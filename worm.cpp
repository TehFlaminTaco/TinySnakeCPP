enum DIR{
    NORTH,
    EAST,
    SOUTH,
    WEST
};

class worm{
    public:
        int x;
        int y;
        worm* tail;
        charmap* worm_map;
        
        worm(int spawn_x, int spawn_y, charmap* spawnedmap){
            x = spawn_x;
            y = spawn_y;
            worm_map = spawnedmap;
            tail = NULL;
        }

        void moveDir(DIR dir){
            switch(dir){
                case NORTH: move(x, y-1);   break;
                case EAST : move(x+1, y);   break;
                case SOUTH: move(x, y+1);   break;
                case WEST : move(x-1, y);   break;
            }
        }

        void move(int tx, int ty){
            if(tx < 1)
                tx = worm_map -> width-2;
            
            if(tx > worm_map -> width-2)
                tx = 1;
            
            if(ty < 1)
                ty = worm_map -> height-2;
            
            if(ty > worm_map -> height-2)
                ty = 1;

            if(tail != NULL)
                tail -> move(x, y);
            
            x = tx;
            y = ty;
        }

        void drawWorm(){
            worm_map -> set(x, y, 'o');
            if(tail != NULL)
                tail -> drawWorm();
        }

        worm* pushTail(){
            if(tail != NULL)
                return tail -> pushTail();
            
            worm* newWorm = new worm(x, y, worm_map);
            tail = newWorm;
            return newWorm;
        }
};