#include <stdlib.h>

class charmap{
    public: 
        int width;
        int height;
        int size;
        char* entry;

        charmap(int w, int h, char fill){
            width = w;
            height = h;
            size = (w+2) * h;
            entry = (char*)malloc(size+1);
            char* cur_char = entry;
            for(int y=0; y < h; y++){
                for(int x=0; x < w; x++){
                    *(cur_char++) = fill;
                }
                *(cur_char++) = '\r';
                *(cur_char++) = '\n';
            }
            *(cur_char++) = 0;  // Null terminated ;)
        };

        void set(int x, int y, char setChar){
            *(entry + (y*(width+2)) + x) = setChar;
        }

        char get(int x, int y){
            return *(entry + (y*(width+2)) + x);
        }

        void rectangle(bool fill, char tofill, int x1, int y1, int w, int h){
            if(fill){
                for(int y=y1; y < y1+h; y++){
                    for(int x=x1; x < x1+w; x++){
                        set(x, y, tofill);
                    }
                }
            }else{
                for(int x=x1; x < x1+w; x++){
                    set(x, y1, tofill);
                    set(x, y1+h-1, tofill);
                }
                for(int y=y1+1; y < y1+h-1; y++){
                    set(x1, y, tofill);
                    set(x1+w-1, y, tofill);
                }
            }
        }
};