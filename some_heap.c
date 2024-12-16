
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "some_heap.h"

#define KEY_NOT_PRESENT -1

heap_t *heap_create(int capacity)
{
    heap_t *heap = (heap_t *)malloc(sizeof(heap_t));
    heap->data = (heap_node_t *)malloc(capacity * sizeof(heap_node_t));
    if (heap->data == NULL)
    {
        free(heap);
        return NULL;
    }

    // Initialize the heap properties
    heap->size = 0;            // The heap is initially empty
    heap->capacity = capacity; // Set the capacity to the provided value

    return heap; // Return the pointer to the newly created heap
}

void heap_free(heap_t *heap)
{
    if (heap != NULL)
    {
        free(heap->data);
    }
}

unsigned int heap_size(heap_t *heap)
{
    return heap->size;
}

unsigned int heap_parent(unsigned int index)
{
    if (index == 0)
    {
        return -1; // No parent for the root node
    }
    return (index - 1) / 2; // Return the parent index
}
unsigned int heap_left_child(unsigned int index)
{
    return 2 * index + 1; // Return the left child index
}
unsigned int heap_right_child(unsigned int index)
{
    return 2 * index + 2; // Return the right child index
}
unsigned int heap_level(unsigned int index)
{
    if (index == 0)
    {
        return 0; // The root node is at level 0
    }
    return (unsigned int)(log2(index + 1)); // Calculate the level
}

void heap_print(heap_t *heap)
{
    for (int ix = 0; ix < heap_size(heap); ix++)
    {
        printf("%3d - %3d : " HEAP_KEY_FORMAT "\n", heap_level(ix), ix,
               heap->data[ix].key);
    }
    printf("\n");
}

void heap_swap(heap_t *heap, int index1, int index2)
{
    if (heap == NULL)
        return; // Check if the heap is NULL

    // Swap the nodes at index1 and index2
    heap_node_t temp = heap->data[index1];   // Temporary storage for node at index1
    heap->data[index1] = heap->data[index2]; // Move node at index2 to index1
    heap->data[index2] = temp;               // Place temp (original node at index1) in index2
}

void heap_bubble_up(heap_t *heap, int index)
{
    if (heap == NULL || index == 0)
        return; // Check if the heap is NULL or if we're at the root

    int parentIndex = (index - 1) / 2; // Calculate the index of the parent node

    // While the current node is less than its parent
    while (index > 0 && heap->data[index].key < heap->data[parentIndex].key)
    {
        heap_swap(heap, index, parentIndex); // Swap with parent
        index = parentIndex;                 // Move index up to parent
        parentIndex = (index - 1) / 2;       // Update parent index
    }
}

void heap_bubble_down(heap_t *heap, int index)
{
    if (heap == NULL)
        return; // Check if the heap is NULL

    int left_child_index;
    int right_child_index;
    int smallest_index;

    while (true)
    {
        left_child_index = 2 * index + 1;  // Left child index
        right_child_index = 2 * index + 2; // Right child index
        smallest_index = index;            // Assume current index is the smallest

        // Compare with left child
        if (left_child_index < heap->size && heap->data[left_child_index].key < heap->data[smallest_index].key)
        {
            smallest_index = left_child_index; // Update smallest index
        }

        // Compare with right child
        if (right_child_index < heap->size && heap->data[right_child_index].key < heap->data[smallest_index].key)
        {
            smallest_index = right_child_index; // Update smallest index
        }

        // If the smallest index is still the current index, we're done
        if (smallest_index == index)
            break;

        // Swap with the smallest child and continue bubbling down
        heap_swap(heap, index, smallest_index);
        index = smallest_index; // Move down to the smallest child's index
    }
}

void heap_insert(heap_t *heap, heap_key_t key, heap_value_t data)
{
    if (heap_size(heap) == heap->capacity)
    {
        return;
    }

    heap->data[heap_size(heap)].key = key;
    heap->data[heap_size(heap)].value = data;
    heap->size++;

    heap_bubble_up(heap, heap_size(heap) - 1);
}

heap_value_t heap_remove_min(heap_t *heap)
{
    if (heap_size(heap) == 0)
    {
        // return NULL; Original
        return (heap_value_t){.as_int = KEY_NOT_PRESENT};
    }

    heap_value_t min = heap->data[0].value;

    heap->size--;

    // move last element to the root
    heap->data[0] = heap->data[heap_size(heap)];

    // then bubble it down to its correct position
    heap_bubble_down(heap, 0);

    return min;
}
