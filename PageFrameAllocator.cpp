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
    memory.resize(numPageFrames * PAGE_FRAME_SIZE);
    std::cout << "Size of memory: " << memory.size() << std::endl;
    
    for(int i = 0; i < numPageFrames; ++i){
        int position = 0;
        int offset = i * PAGE_FRAME_SIZE;
        for(int k = 3 + offset; k >= offset; --k){
            memory[k] = ((((i + 1) * PAGE_FRAME_SIZE) >> (8 * position)) & 0xFF);
            position++;
        }
    }
    page_frames_total = numPageFrames;
    page_frames_free = numPageFrames;
    free_list_head = 0xFFFFFFFF;
}

bool PageFrameAllocator::Allocate(uint32_t count, std::vector<uint32_t> &page_frames){
/* Push the numbers of all the allocated page frames onto the back of the 
 * vector page_frames (specified as the second argument). If the number of free 
 * page frames is less than the count argument, then no page frames should be 
 * allocated, and method should return false. 
 * If page frames are successfully allocated, return true.*/
    if(page_frames_free < count)
        return false;
    
    //TODO: push allocated page frames onto back of page_frames
    
    page_frames_free -= count;
    return true;
}
bool PageFrameAllocator::Deallocate(uint32_t count, std::vector<uint32_t> &page_frames){
/* Return the last count page frame numbers from the vector page_frames to the 
 * free list. Page frame numbers should be popped from the back of the page_frames
 * vector as they are returned to the free list. Returns true if
 * count <= page_frames.size() otherwise returns false without freeing any page frames
 */

}

void PageFrameAllocator::view5Bytes(){
    for(int i = 0; i < page_frames_total; ++i){
        for(int j = (i * PAGE_FRAME_SIZE); j < (5 + (i * PAGE_FRAME_SIZE)); ++j){
            std::cout << +memory[j] << ", ";
        }
        std::cout << std::endl;
    }
}


PageFrameAllocator::~PageFrameAllocator() {}

