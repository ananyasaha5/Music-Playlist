#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct song{
    char title[100];
    char artist[100];
    float duration;
    
    struct song *next;
    struct song *prev;
};

struct song *head=NULL;
struct song *tail=NULL;
struct song *current=NULL;

void addSong(){
    struct song *newsong= (struct song*)malloc(sizeof(struct song));
    getchar();
    printf("Enter Song Title: ");
    fgets(newsong->title, sizeof(newsong->title), stdin);
    newsong->title[strcspn(newsong->title, "\n")] = '\0';
    
    printf("Enter Artist's Name: ");
    fgets(newsong->artist, sizeof(newsong->artist), stdin);
    newsong->artist[strcspn(newsong->artist, "\n")] = '\0';
    
    printf("Enter duration(in mins):");
    scanf("%f",&newsong->duration);
    
    while ((getchar()) != '\n' && getchar() != EOF);
    
    newsong->next=NULL;
    newsong->prev=tail;
    
    if(head==NULL){
        head=tail=newsong;
    }else{
        tail->next=newsong;
        newsong->prev=tail;
        tail=newsong;
    }
    if(current==NULL){
        current=newsong;
    }
    printf("Song added successfully ✅\n");
}

void display(){
    struct song *temp=head;
    if(temp==NULL){
        printf("Playlist is empty.\n");
        return;
    }
    printf("\n Playlist🎶:\n");
    while(temp!=NULL){
        if(temp==current)  
            printf("👉");
        else 
            printf(" ~ ");
            
        printf("Title: %s\n   Artist:%s\n   duration:%.2f min\n",temp->title,temp->artist,temp->duration); 
        temp=temp->next;
    }
}    

void playNext(){
    if(current==NULL || current->next==NULL){
        printf("No Next Song ⚠️.\n");
    }else{
        current=current->next;
        printf("\nNext song Playing ▶ : \n%s by %s \n",current->title,current->artist);
    }
}

void playPrev(){
    if(current==NULL || current->prev==NULL){
        printf("No previous song ⚠️\n");
    }
    else{
        current=current->prev;
            printf("\npreviously playing ◀️ :  \n%s by %s\n",current->title,current->artist);
        }
    }

void delSong(){
    char name[100];
    getchar();
    printf("Enter song to be deleted:");
    fgets(name,sizeof(name),stdin);
    name[strcspn(name,"\n")]='\0';
    
    struct song*temp=head;
    
    while(temp!=NULL){
        if(strcasecmp(temp->title,name)==0){
            if(temp==head) head=temp->next;
            if(temp==tail) tail=temp->prev;
            if(temp->prev) temp->prev->next=temp->next;
            if(temp->next) temp->next->prev=temp->prev;
            if(current==temp){
                if(temp->next) current=temp->next;
                else if(temp->prev) current=temp->prev;
                else current=NULL;
            }
            struct song*toDel=temp;
            temp=NULL;
            free(toDel);
            printf("Song deleted successfully 🧹️️️️\n");
            return;
        }
        temp=temp->next;
    }
    printf("Song not found ❌\n");
    
}

void shuffle(){
    int count=0;
    struct song*temp=head;
    while(temp){
        count++;
        temp=temp->next;
    }
    if(count==0) printf("Playlist is empty\n");

    int shuff=rand()%count;
    temp=head;
    for(int i=0;i<shuff;i++){
        temp=temp->next;
    }
    current=temp;
    printf("Shuffle Playing 🔀: %s by %s\n",current->title,current->artist);
}

void TotalDuration(){
    float total=0;
    struct song*temp=head;
    while(temp){
        total+=temp->duration;
        temp=temp->next;
    }
    printf("Total Playlist Duration ⏱️: %.2f mins\n",total);
}

void searchByTitle(){
    char name[100];
    getchar();
    printf("Enter name of the song:");
    fgets(name,sizeof(name),stdin);
    name[strcspn(name,"\n")]='\0';

    struct song*temp=head;
    int found=0;

    while(temp!=NULL){
        if(strcasecmp(temp->title,name)==0){
            printf("Found 🔍: %s by %s (%.2f mins)\n",temp->title,temp->artist,temp->duration);
            found=1;
        }
        temp=temp->next;
    }
    if(!found) printf("No songs found by that title ❌\n");
}

void edit(){
    char name[100];
    getchar();
    printf("Enter song title to edit:");
    fgets(name, sizeof(name),stdin);
    name[strcspn(name,"\n")]='\0';
    struct song*temp=head;

    while(temp!=NULL){
        if(strcasecmp(temp->title,name)==0){
            printf("Editing 🎯: %s\n",temp->title);

            printf("Enter New Title:");
            fgets(temp->title,sizeof(temp->title),stdin);
            temp->title[strcspn(temp->title,"\n")]='\0';

            printf("Enter New Artist:");
            fgets(temp->artist,sizeof(temp->artist),stdin);
            temp->artist[strcspn(temp->artist,"\n")]='\0';

            printf("Enter New duration:");
            scanf("%f",&temp->duration);

            printf("Songs details updated ✅\n");
            return;
        }
        temp=temp->next;
    }
    printf("Song not found ❌\n");
}
int main(){
    int choice;
    do{
        printf("\n===Music Playlist 🎧 ===\n");
        printf("1. Add songs\n");
        printf("2. Display songs\n");
        printf("3. Play Next song\n");
        printf("4. Play Previous song\n");
        printf("5. Delete a song\n");
        printf("6. Shuffle play\n");
        printf("7. Show total duration of songs\n");
        printf("8. Search by title \n");
        printf("9. Edit song\n");
        printf("10. Exit\n");
        printf("Choose an option:");
        scanf("%d",&choice);

        switch(choice){
            case 1: {int addmore;
        do{
        addSong();
        printf("Do you want to add more songs?(1/0)");
        scanf("%d",&addmore);
        } while(addmore==1);
        break; 
    }
            case 2: display(); break;
            case 3: playNext(); break;
            case 4: playPrev(); break;
            case 5: delSong(); break;
            case 6: shuffle(); break;
            case 7: TotalDuration(); break;
            case 8: searchByTitle(); break;
            case 9: edit(); break;
            case 10: printf("Exiting 👋"); break;
            default: printf("Invalid option ⚠️");
        }
    }while (choice !=10);
}
