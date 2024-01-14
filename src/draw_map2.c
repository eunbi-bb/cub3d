#include "cub3d.h"

#define	mapS	64 //map cube size
// #define mapX	33
// #define mapY	14

int FixAng(float a){ if(a>359){ a-=360;} if(a<0){ a+=360;} return a;}
float distance(ax,ay,bx,by,ang){ return cos(deg2rad(ang))*(bx-ax)-sin(deg2rad(ang))*(by-ay);}
float pdx,pdy;
// float frame1,frame2,fps;

void	draw_square(int x, int y_end, long long color)
{
	int	y = 0;
	while (y < y_end)
	{
		mlx_put_pixel(image, x, y_end, color);
		y++;
	}
}

void draw_2d_map(t_data *data)
{
	int x,y,xo,yo;
	for(y=0; data->file.map.map_int_arr[y] != NULL; y++)
	{
		for(x=0; data->file.map.map_int_arr[y][x] != NULL; x++)
		{
   			xo=x*mapS; yo=y*mapS;
			if(data->file.map.map_int_arr[y][x] != 0)
				draw_square(xo, yo, COLOR_N);
			else
				draw_square(xo, yo, COLOR_BACK);
			// glBegin(GL_QUADS); 
   			// glVertex2i( 0   +xo+1, 0   +yo+1); 
   			// glVertex2i( 0   +xo+1, mapS+yo-1); 
   			// glVertex2i( mapS+xo-1, mapS+yo-1);  
   			// glVertex2i( mapS+xo-1, 0   +yo+1); 
   			// glEnd();
		} 
 	}
}

void drawPlayer2D(t_data *data)
{
	int	x,y;
	x = data->player->x;
	y = data->player->y;
	while (x <= x + 10)
	{
		mlx_put_pixel(image, x, y, COLOR_E);
		while (y <= y + 10)
		{
			mlx_put_pixel(image, x, y, COLOR_E);
			y++;
		}
		x++;
	}
	// glColor3f(1,1,0);   glPointSize(8);    glLineWidth(4);
	// glBegin(GL_POINTS); glVertex2i(data->player->x,data->player->y); glEnd();
	// glBegin(GL_LINES);  glVertex2i(data->player->x,data->player->y); glVertex2i(data->player->x+pdx*20,data->player->y+pdy*20); glEnd();
}


// void draw_2d_rays(t_data *data)
// {
//  glColor3f(0,1,1); glBegin(GL_QUADS); glVertex2i(526,  0); glVertex2i(1006,  0); glVertex2i(1006,160); glVertex2i(526,160); glEnd();	
//  glColor3f(0,0,1); glBegin(GL_QUADS); glVertex2i(526,160); glVertex2i(1006,160); glVertex2i(1006,320); glVertex2i(526,320); glEnd();	 	
	
//  int r,mx,my,mp,dof,side; float vx,vy,rx,ry,ra,xo,yo,disV,disH; 
 
//  ra=FixAng(data->player->th+30);                                                              //ray set back 30 degrees
 
//  for(r=0;r<60;r++)
//  {
//   int vmt=0,hmt=0;                                                              //vertical and horizontal map texture number 
//   //---Vertical--- 
//   dof=0; side=0; disV=100000;
//   float Tan=tan(deg2rad(ra));
//        if(cos(deg2rad(ra))> 0.001){ rx=(((int)data->player->x >> 6)<<6)+64;      ry=(data->player->x-rx)*Tan+data->player->y; xo= 64; yo=-xo*Tan;}//looking left
//   else if(cos(deg2rad(ra))<-0.001){ rx=(((int)data->player->x>>6)<<6) -0.0001; ry=(data->player->x-rx)*Tan+data->player->y; xo=-64; yo=-xo*Tan;}//looking right
//   else { rx=data->player->x; ry=data->player->y; dof=8;}                                                  //looking up or down. no hit  

//   while(dof<8) 
//   { 
//    mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;                     
// 	if (mp>0 && mp<mapX*mapY &&  data->file.map.map_int_arr[mp]>0)
// 	{	
// 		vmt= data->file.map.map_int_arr[mp]-1;
//    		dof=8; 
// 		disV=cos(deg2rad(ra))*(rx-data->player->x)-sin(deg2rad(ra))*(ry-data->player->y);
// 	}//hit         
// 	else
// 	{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
//   } 
//   vx=rx; vy=ry;

//   //---Horizontal---
//   dof=0; disH=100000;
//   Tan=1.0/Tan; 
//        if(sin(deg2rad(ra))> 0.001){ ry=(((int)data->player->y>>6)<<6) -0.0001; rx=(data->player->y-ry)*Tan+data->player->x; yo=-64; xo=-yo*Tan;}//looking up 
//   else if(sin(deg2rad(ra))<-0.001){ ry=(((int)data->player->y>>6)<<6)+64;      rx=(data->player->y-ry)*Tan+data->player->x; yo= 64; xo=-yo*Tan;}//looking down
//   else{ rx=data->player->x; ry=data->player->y; dof=8;}                                                   //looking straight left or right
 
//   while(dof<8) 
//   { 
//    mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;                          
//    if(mp>0 && mp<mapX*mapY &&  data->file.map.map_int_arr[mp]>0){ hmt= data->file.map.map_int_arr[mp]-1; dof=8; disH=cos(deg2rad(ra))*(rx-data->player->x)-sin(deg2rad(ra))*(ry-data->player->y);}//hit         
//    else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
//   } 
  
//   float shade=1;
//   glColor3f(0,0.8,0);
//   if(disV<disH){ hmt=vmt; shade=0.5; rx=vx; ry=vy; disH=disV; glColor3f(0,0.6,0);}//horizontal hit first
//   glLineWidth(2); glBegin(GL_LINES); glVertex2i(data->player->x,data->player->y); glVertex2i(rx,ry); glEnd();//draw 2D ray
// 	}
// }

void drawRays2D()
{
 glColor3f(0,1,1); glBegin(GL_QUADS); glVertex2i(526,  0); glVertex2i(1006,  0); glVertex2i(1006,160); glVertex2i(526,160); glEnd();	
 glColor3f(0,0,1); glBegin(GL_QUADS); glVertex2i(526,160); glVertex2i(1006,160); glVertex2i(1006,320); glVertex2i(526,320); glEnd();	 	
	
 int r,mx,my,mp,dof,side; float vx,vy,rx,ry,ra,xo,yo,disV,disH; 
 
 ra=FixAng(pa+30);                                                              //ray set back 30 degrees
 
 for(r=0;r<60;r++)
 {
  //---Vertical--- 
  dof=0; side=0; disV=100000;
  float Tan=tan(degToRad(ra));
       if(cos(degToRad(ra))> 0.001){ rx=(((int)px>>6)<<6)+64;      ry=(px-rx)*Tan+py; xo= 64; yo=-xo*Tan;}//looking left
  else if(cos(degToRad(ra))<-0.001){ rx=(((int)px>>6)<<6) -0.0001; ry=(px-rx)*Tan+py; xo=-64; yo=-xo*Tan;}//looking right
  else { rx=px; ry=py; dof=8;}                                                  //looking up or down. no hit  

  while(dof<8) 
  { 
   mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;                     
   if(mp>0 && mp<mapX*mapY && map[mp]==1){ dof=8; disV=cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py);}//hit         
   else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
  } 
  vx=rx; vy=ry;

  //---Horizontal---
  dof=0; disH=100000;
  Tan=1.0/Tan; 
       if(sin(degToRad(ra))> 0.001){ ry=(((int)py>>6)<<6) -0.0001; rx=(py-ry)*Tan+px; yo=-64; xo=-yo*Tan;}//looking up 
  else if(sin(degToRad(ra))<-0.001){ ry=(((int)py>>6)<<6)+64;      rx=(py-ry)*Tan+px; yo= 64; xo=-yo*Tan;}//looking down
  else{ rx=px; ry=py; dof=8;}                                                   //looking straight left or right
 
  while(dof<8) 
  { 
   mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;                          
   if(mp>0 && mp<mapX*mapY && map[mp]==1){ dof=8; disH=cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py);}//hit         
   else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
  } 
  
  glColor3f(0,0.8,0);
  if(disV<disH){ rx=vx; ry=vy; disH=disV; glColor3f(0,0.6,0);}                  //horizontal hit first
  glLineWidth(2); glBegin(GL_LINES); glVertex2i(px,py); glVertex2i(rx,ry); glEnd();//draw 2D ray
    
  int ca=FixAng(pa-ra); disH=disH*cos(degToRad(ca));                            //fix fisheye 
  int lineH = (mapS*320)/(disH); if(lineH>320){ lineH=320;}                     //line height and limit
  int lineOff = 160 - (lineH>>1);                                               //line offset
  
  glLineWidth(8);glBegin(GL_LINES);glVertex2i(r*8+530,lineOff);glVertex2i(r*8+530,lineOff+lineH);glEnd();//draw vertical wall  

  ra=FixAng(ra-1);                                                              //go to next ray
 }
}

void display(struct mlx_key_data keydata, void *game_data)
{
	keys_t key = keydata.key;
    t_data *data = (t_data *)game_data;
 //frames per second
//  frame2=mlx_get_time(); fps=(frame2-frame1); frame1=mlx_get_time(); 

 //buttons
 	if(key == MLX_KEY_A)
 { data->player->th+=5; data->player->th=FixAng(data->player->th); pdx=cos(deg2rad(data->player->th)); pdy=-sin(deg2rad(data->player->th));} 	
 	if(key == MLX_KEY_D)
 { data->player->th-=5; data->player->th=FixAng(data->player->th); pdx=cos(deg2rad(data->player->th)); pdy=-sin(deg2rad(data->player->th));} 
	if(key == MLX_KEY_W)
 { data->player->x += pdx*5; data->player->y += pdy*5;}
	if(key == MLX_KEY_S)
 { data->player->x -= pdx*5; data->player->y -= pdy*5;} 
//  int xo=0; if(pdx<0){ xo=-20;} else{ xo=20;}                                    //x offset to check map
//  int yo=0; if(pdy<0){ yo=-20;} else{ yo=20;}                                    //y offset to check map
//  int ipx=data->player->x/64.0, ipx_add_xo=(data->player->x+xo)/64.0, ipx_sub_xo=(data->player->x-xo)/64.0;             //x position and offset
//  int ipy=data->player->y/64.0, ipy_add_yo=(data->player->y+yo)/64.0, ipy_sub_yo=(data->player->y-yo)/64.0;             //y position and offset
//  if(key == MLX_KEY_W)                                                                  //move forward
//  {  
//   if( data->file.map.map_int_arr[ipy*mapX        + ipx_add_xo]==0){ data->player->x+=pdx*0.2*fps;}
//   if( data->file.map.map_int_arr[ipy_add_yo*mapX + ipx       ]==0){ data->player->y+=pdy*0.2*fps;}
//  }
//  if(key == MLX_KEY_S)                                                                  //move backward
//  { 
//   if( data->file.map.map_int_arr[ipy*mapX        + ipx_sub_xo]==0){ data->player->x-=pdx*0.2*fps;}
//   if( data->file.map.map_int_arr[ipy_sub_yo*mapX + ipx       ]==0){ data->player->y-=pdy*0.2*fps;}
//  } 

//  glutPostRedisplay();
 
//  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
printf("HERE1\n");
 draw_2d_map(data);
 printf("HERE2\n");
 drawPlayer2D(data);
printf("HERE3\n");
//  draw_2d_rays(data);
//  glutSwapBuffers();  
}
