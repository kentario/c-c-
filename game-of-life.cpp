#include <iostream>
#include <cstring>

using namespace std;

int offset (int size_width, int size_height, int horiz_off, int vert_off)
{
  if (horiz_off < 0 || vert_off < 0 || horiz_off >= size_width || vert_off >= size_height) {
    return -1;
  }
  return (size_width * vert_off) + horiz_off;
}

int count_adjacent (int x, int y, bool pixels_on[], int width, int height)
{
  int count = 0;
  for (int rel_y = -1; rel_y < 2; rel_y++) {
    for (int rel_x = -1; rel_x < 2; rel_x++) {
      int this_offset = offset(width, height, x + rel_x, y + rel_y);
      if ((rel_x != 0 || rel_y != 0) && this_offset != -1) {
	if (pixels_on[this_offset]) {
	  count++;
	}
      }
    }
  }
  return count;
}

int main ()
{
  int width = 15;
  int height = 25;
  int current_x;
  int current_y;

  bool pixels_on[width * height];
  int adjacent_on[width][height];
  memset(pixels_on, false, sizeof(pixels_on));
  memset(adjacent_on, 0, sizeof(adjacent_on));

  pixels_on[offset(width, height, 3, 3)] = true;
  pixels_on[offset(width, height, 4, 3)] = true;
  pixels_on[offset(width, height, 5, 3)] = true;
  pixels_on[offset(width, height, 6, 3)] = true;
  pixels_on[offset(width, height, 7, 3)] = true;
  pixels_on[offset(width, height, 8, 3)] = true;
  pixels_on[offset(width, height, 2, 4)] = true;
  pixels_on[offset(width, height, 8, 4)] = true;
  pixels_on[offset(width, height, 8, 5)] = true;
  pixels_on[offset(width, height, 2, 6)] = true;
  pixels_on[offset(width, height, 7, 6)] = true;
  pixels_on[offset(width, height, 4, 7)] = true;
  pixels_on[offset(width, height, 5, 7)] = true;
  
  // Printing the screen.
  for (int i = 0; i < 15; i++) {
    for (current_y = 0; current_y < height; current_y++) {
      for (current_x = 0; current_x < width; current_x++) {
	if (pixels_on[offset(width, height, current_x, current_y)]) {
	  cout << "#";
	} else {
	  cout << ".";
	}
	adjacent_on[current_x][current_y] = count_adjacent(current_x, current_y, pixels_on, width, height);
      }
      cout << "\n";
    }
    
    cout << "\n";
    
    for (current_y = 0; current_y < height; current_y++) {
      for (current_x = 0; current_x < width; current_x++) {
	int this_offset = offset(width, height, current_x, current_y);
	
	if (// Any live cell with two or three live neighbours survives.
	    (pixels_on[this_offset] == true && (adjacent_on[current_x][current_y] == 2 || adjacent_on[current_x][current_y] == 3)) ||
	    // Any dead cell with three live neighbours becomes a live cell.
	    (pixels_on[this_offset] == false && adjacent_on[current_x][current_y] == 3)) {
	  pixels_on[this_offset] = true;
	} else {
	  // All other live cells die in the next generation. Similarly, all other dead cells stay dead.
	  pixels_on[this_offset] = false;
	}
      }
    }
  }
}
