// Laura Toma
// oct 2023

#ifndef __drainage_h
#define __drainage_h


#include "grid.h"

typedef struct _point{
  int x,y;
} point;





/*
  elev_grid: input elevation grid
  r, c: row and column of a point in the grid 
  return: the d8 flow direction of (r,c)
  - Points on the edge of the grid  are set to flow outside.
  - Points with elev=nodata, return  nodata
  - Points  with all neighbors > , return  PIT_DIR
  - Points with all neighbors  at same elevation, return FLAT_DIR
  
  d8 dir convention:
  32 64 128
  16  x  1
  8   4  2
*/
int d8(const Grid* elev_grid, int r, int c); 



/* fd_grid: input 
   (a,b) and (c,d) are points in the grid 
   return 1 if (a, b) is a neighbor of (c, d) and fd_grid[(a,b)]  points towards (c, d)
   return 0 otherwise 

   d8 dir convention: 
   32 64 128
   16  x  1
   8   4  2
*/
int flows_into(const Grid* fd_grid, int a, int b, int c, int d);

  
/*
  elev_grid: input elevation grid
  fd_grid: output FD grid, initialized
  
  populate fd_grid with d8 flow direction values; assign all points
  with no lower neighbors either FLAT_DIR or PIT_DIR
*/
void compute_d8flowdir_grid_skipflat(const Grid* elev_grid,  Grid* fd_grid);


/*
  elev_grid: input elevation grid
  fd_grid: output FD grid, initialized

  populates fd_grid with d8 flow direction values. The FD of points
  that are on flat areas that have outlets is set towards the outlets.
*/
void compute_d8flowdir_grid_withplateaus(const Grid* elev_grid,  Grid* fd_grid);


/*
  elev_grid: input elevation grid
  fd_grid:   input FD grid
  fa_grid:    output FA grid 
  return the flow value of cell (r, c)
*/
int compute_flow_at_point(const Grid* elev_grid, const Grid* fd_grid, Grid* fa_grid, int r, int c); 
  

/*
  elev_grid: input elevation grid
  fd_grid: input FD grid
  fa_grid: output FA grid, assume initialized

  distribute flow according to fd_grid and populate fa_grid with FA values 
*/
void compute_fa_grid(const Grid* elev_grid, const Grid* fd_grid,  Grid* fa_grid);



/*
  elev_grid: input elevation grid
  flooded_grid: output flooded grid.
  
  floods elev_grid from the outside and populates flooded_grid with
  values; flooded[i,j] represents the value of water at [i,j] when the
  terrain is flooded.
 */
void flood_sinks(const Grid* elev_grid, Grid* flooded_grid);



#endif 



