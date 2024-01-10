#include "cub3d.h"

#define	mapS	64 //map cube size
#define mapX	33
#define mapY	14

float FixAng(float a){ if(a>359){ a-=360;} if(a<0){ a+=360;} return a;}
float distance(ax,ay,bx,by,ang){ return cos(degToRad(ang))*(bx-ax)-sin(degToRad(ang))*(by-ay);}
float pdx,pdy,pa;
float frame1,frame2,fps;

void draw_2d_map(t_data *data)
{
	int x,y,xo,yo;
	for(y=0;y<mapY;y++)
	{
		for(x=0;x<mapX;x++)
		{
			if(data->file.map.map_int_arr[y*mapX+x]>0)
				glColor3f(1,1,1);
			else
				glColor3f(0,0,0);
   			xo=x*mapS; yo=y*mapS;
			glBegin(GL_QUADS); 
   			glVertex2i( 0   +xo+1, 0   +yo+1); 
   			glVertex2i( 0   +xo+1, mapS+yo-1); 
   			glVertex2i( mapS+xo-1, mapS+yo-1);  
   			glVertex2i( mapS+xo-1, 0   +yo+1); 
   			glEnd();
		} 
 	}
}

void drawPlayer2D(t_data *data)
{
	glColor3f(1,1,0);   glPointSize(8);    glLineWidth(4);
	glBegin(GL_POINTS); glVertex2i(data->player->x,data->player->y); glEnd();
	glBegin(GL_LINES);  glVertex2i(data->player->x,data->player->y); glVertex2i(data->player->x+pdx*20,data->player->y+pdy*20); glEnd();
}


void draw_2d_rays(t_data *data)
{
 data->file.map.map_int_arr;
 glColor3f(0,1,1); glBegin(GL_QUADS); glVertex2i(526,  0); glVertex2i(1006,  0); glVertex2i(1006,160); glVertex2i(526,160); glEnd();	
 glColor3f(0,0,1); glBegin(GL_QUADS); glVertex2i(526,160); glVertex2i(1006,160); glVertex2i(1006,320); glVertex2i(526,320); glEnd();	 	
	
 int r,mx,my,mp,dof,side; float vx,vy,rx,ry,ra,xo,yo,disV,disH; 
 
 ra=FixAng(pa+30);                                                              //ray set back 30 degrees
 
 for(r=0;r<60;r++)
 {
  int vmt=0,hmt=0;                                                              //vertical and horizontal map texture number 
  //---Vertical--- 
  dof=0; side=0; disV=100000;
  float Tan=tan(degToRad(ra));
       if(cos(degToRad(ra))> 0.001){ rx=(((int)data->player->x >> 6)<<6)+64;      ry=(data->player->x-rx)*Tan+data->player->y; xo= 64; yo=-xo*Tan;}//looking left
  else if(cos(degToRad(ra))<-0.001){ rx=(((int)data->player->x>>6)<<6) -0.0001; ry=(data->player->x-rx)*Tan+data->player->y; xo=-64; yo=-xo*Tan;}//looking right
  else { rx=data->player->x; ry=data->player->y; dof=8;}                                                  //looking up or down. no hit  

  while(dof<8) 
  { 
   mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;                     
   if(mp>0 && mp<mapX*mapY &&  data->file.map.map_int_arr[mp]>0){ vmt= data->file.map.map_int_arr[mp]-1; dof=8; disV=cos(degToRad(ra))*(rx-data->player->x)-sin(degToRad(ra))*(ry-data->player->y);}//hit         
   else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
  } 
  vx=rx; vy=ry;

  //---Horizontal---
  dof=0; disH=100000;
  Tan=1.0/Tan; 
       if(sin(degToRad(ra))> 0.001){ ry=(((int)data->player->y>>6)<<6) -0.0001; rx=(data->player->y-ry)*Tan+data->player->x; yo=-64; xo=-yo*Tan;}//looking up 
  else if(sin(degToRad(ra))<-0.001){ ry=(((int)data->player->y>>6)<<6)+64;      rx=(data->player->y-ry)*Tan+data->player->x; yo= 64; xo=-yo*Tan;}//looking down
  else{ rx=data->player->x; ry=data->player->y; dof=8;}                                                   //looking straight left or right
 
  while(dof<8) 
  { 
   mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;                          
   if(mp>0 && mp<mapX*mapY &&  data->file.map.map_int_arr[mp]>0){ hmt= data->file.map.map_int_arr[mp]-1; dof=8; disH=cos(degToRad(ra))*(rx-data->player->x)-sin(degToRad(ra))*(ry-data->player->y);}//hit         
   else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
  } 
  
  float shade=1;
  glColor3f(0,0.8,0);
  if(disV<disH){ hmt=vmt; shade=0.5; rx=vx; ry=vy; disH=disV; glColor3f(0,0.6,0);}//horizontal hit first
  glLineWidth(2); glBegin(GL_LINES); glVertex2i(data->player->x,data->player->y); glVertex2i(rx,ry); glEnd();//draw 2D ray
	}
}

void display(struct mlx_key_data keydata, void *game_data)
{
	keys_t key = keydata.key;
    t_data *data = (t_data *)game_data;
 //frames per second
 frame2=glutGet(GLUT_ELAPSED_TIME); fps=(frame2-frame1); frame1=glutGet(GLUT_ELAPSED_TIME); 

 //buttons
 if(key == MLX_KEY_A){ pa+=0.2*fps; pa=FixAng(pa); pdx=cos(degToRad(pa)); pdy=-sin(degToRad(pa));} 	
 if(key == MLX_KEY_D){ pa-=0.2*fps; pa=FixAng(pa); pdx=cos(degToRad(pa)); pdy=-sin(degToRad(pa));} 

 int xo=0; if(pdx<0){ xo=-20;} else{ xo=20;}                                    //x offset to check map
 int yo=0; if(pdy<0){ yo=-20;} else{ yo=20;}                                    //y offset to check map
 int ipx=data->player->x/64.0, ipx_add_xo=(data->player->x+xo)/64.0, ipx_sub_xo=(data->player->x-xo)/64.0;             //x position and offset
 int ipy=data->player->y/64.0, ipy_add_yo=(data->player->y+yo)/64.0, ipy_sub_yo=(data->player->y-yo)/64.0;             //y position and offset
 if(key == MLX_KEY_W)                                                                  //move forward
 {  
  if( data->file.map.map_int_arr[ipy*mapX        + ipx_add_xo]==0){ data->player->x+=pdx*0.2*fps;}
  if( data->file.map.map_int_arr[ipy_add_yo*mapX + ipx       ]==0){ data->player->y+=pdy*0.2*fps;}
 }
 if(key == MLX_KEY_S)                                                                  //move backward
 { 
  if( data->file.map.map_int_arr[ipy*mapX        + ipx_sub_xo]==0){ data->player->x-=pdx*0.2*fps;}
  if( data->file.map.map_int_arr[ipy_sub_yo*mapX + ipx       ]==0){ data->player->y-=pdy*0.2*fps;}
 } 

 glutPostRedisplay();
 
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
 drawMap2D();
 drawPlayer2D();
 drawRays2D();
 glutSwapBuffers();  
}

void	draw_map(t_data *data)
{
	draw_2d_map(data);
	drawPlayer2D(data);
	draw_2d_rays(data);
	display(data);
}