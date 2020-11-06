#define Q1 1
#define Q2 2
int events = 0;
bool eventIsSet(int ev){
   return (events & ev);
   }

void clearEvent(int ev){
  events = events & (~ev);
}

void setEvent(int ev){
  events = ev | ev;
}

