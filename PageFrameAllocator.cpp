/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PageFrameAllocator.cpp
 * Author: Tristan Gay
 * 
 * Created on January 27, 2018, 12:39 AM
 */

#include "PageFrameAllocator.h"

#include <iostream>
#include <cstring>


/* -- Linked List Implementation --
     * Contains the free page frames in the form of a linked list. 
     * The "links" are page frame numbers (which are stored in 
     * the first four bytes of a block). The links indicate the
     * next free page frame in the list. The last page frame on 
     * the free list has link 0xFFFFFFFF. The head "pointer" is just
     * the number of the first page frame in the list (0xFFFFFFFF if empty).
     * Page frame numbered 'n' consists of the block of 0x1000 bytes
     * (uint8_t) starting at address n*0x1000 in the memory vector. */

PageFrameAllocator::PageFrameAllocator(uint32_t numPageFrames){
/* Should resize memory memory vector to numPageFrames * 0x1000 
 * Then build free list consistent of all page frames in memory.
 * Initialize other class member data variables as needed. */
    memory.resize(numPageFrames * PAGE_FRAME_SIZE, 0);
    int pos = 0;
    for(uint32_t i = 1; i <= numPageFrames; ++i){
        memcpy(&memory[((i-1)*PAGE_FRAME_SIZE)], &i, sizeof(uint32_t));
    }
    //Initialize class member variables
    allocated_pages.resize(numPageFrames, 0);
    page_frames_total = numPageFrames; 
    page_frames_free = numPageFrames;
    free_list_head = 0x1;
}

bool PageFrameAllocator::Allocate(uint32_t count, std::vector<uint32_t> &page_frames){
/* Push the numbers of all the allocated page frames onto the back of the 
 * vector page_frames (specified as the second argument). If the number of free 
 * page frames is less than the count argument, then no page frames should be 
 * allocated, and method should return false. 
 * If page frames are successfully allocated, return true.*/
    if(page_frames_free < count)
    { 
        return false;
    }
  
    
    //TODO: push allocated page frames onto back of page_frames
    else
    {
    page_frames.push_back(free_list_head);
    page_frames_free -= count;
    return true;
    }
}
bool PageFrameAllocator::Deallocate(uint32_t count, std::vector<uint32_t> &page_frames){
/* Return the last count page frame numbers from the vector page_frames to the 
 * free list. Page frame numbers should be popped from the back of the page_frames
 * vector as they are returned to the free list. Returns true if
 * count <= page_frames.size() otherwise returns false without freeing any page frames
 */
    if(count<=page_frames.size())
    {
        page_frames_free +=count;
       free_list_head=page_frames.back();
        page_frames.pop_back();
    }
    else
    {
        return false;
    }
    

}

void PageFrameAllocator::view5Bytes(){
    for(int i = 0; i < page_frames_total; ++i){
        uint32_t temp;
        memcpy(&temp, &memory[i*PAGE_FRAME_SIZE], sizeof(uint32_t));
        std::cout << "Page frame " << +i << " points to " << +temp << std::endl;
    }
}


PageFrameAllocator::~PageFrameAllocator() {}

