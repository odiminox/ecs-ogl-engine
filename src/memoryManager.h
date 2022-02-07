//
//  memoryManager.h
//  oglApp
//
//  Created by SimonJordan on 23/03/2013.
//  Copyright (c) 2013 Simon Jordan. All rights reserved.
//

#ifndef __oglApp__memoryManager__
#define __oglApp__memoryManager__
#include <stddef.h>
//Adding functionality to this file on a needed basis.
template <class T>
void safeDelete(T* object) {
    if(NULL != object){
        object = NULL;
        delete object;
    }
}


#endif /* defined(__oglApp__memoryManager__) */
