#include "cub3d.h"

#define mapX  25      //map width
#define mapY  12      //map height
#define mapS  64      //map cube size

static mlx_image_t  *image;

void draw_square(int xo, int yo, long long color)
{
	int x = xo;
	int y = yo;
	while (x <= xo + mapS && (xo + mapS) <= MAPX * mapS)
	{
		while (y <= yo + mapS && (yo + mapS) <= MAPY * mapS)
		{
			printf("x : %d\n", x);
			printf("y : %d\n", y);
			printf("image : %d\n", image == NULL ? 0 : 1);
			printf("color : %lld\n", color);
			//mlx_put_pixel(image, x, y, color);  // Vertical line
			y++;
		}
		x++;
	}
}

void drawMap2D(t_data *data)
{
 int	xo,yo;
 for(int y=0; y < mapY; y++)
 {
	// printf("yo : %d\n", yo);
	for(int x=0; x < mapX; x++)
	{
		yo=y*mapS;
		xo=x*mapS;
		// printf("xo : %d\n", xo);
		if(data->file.map.map_int_arr[y][x] == 1)
		{
			// printf("map[%d][%d] cell : %d\n", y, x, data->file.map.map_int_arr[y][x]);
			draw_square(xo, yo, COLOR_N);
		}
		else
		{
			// printf("map[%d][%d] cell : %d\n", y, x, data->file.map.map_int_arr[y][x]);
			draw_square(xo, yo, COLOR_BACK);
		}
	} 
 }
 printf("drawMap2D\n");
}

float	degToRad(int a) { return a*M_PI/180.0;}
int		FixAng(int a){ if(a>359){ a-=360;} if(a<0){ a+=360;} return a;}
float	px,py,pdx,pdy,pa;
// float	distance(ax,ay,bx,by,ang){ return cos(degToRad(ang))*(bx-ax)-sin(degToRad(ang))*(by-ay);}

void drawPlayer2D(t_data *data)
{
	double	x,y;
	x = data->player->x;
	y = data->player->y;
	printf("x : %f\n", x);
	printf("y : %f\n", y);
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
	printf("drawPlayer2D\n");
}

// void drawRays2D(t_data *data)
// {
// 	// glColor3f(0,1,1); glBegin(GL_QUADS); glVertex2i(526,  0); glVertex2i(1006,  0); glVertex2i(1006,160); glVertex2i(526,160); glEnd();	
// 	// glColor3f(0,0,1); glBegin(GL_QUADS); glVertex2i(526,160); glVertex2i(1006,160); glVertex2i(1006,320); glVertex2i(526,320); glEnd();	 	
		
// 	int r,mx,my,mp,dof,side; 
// 	float vx,vy,rx,ry,ra,xo,yo,disV,disH; 
	
// 	ra=FixAng( + 30);                                                              //ray set back 30 degrees
	
// 	for(r=0;r<60;r++)
// 	{
// 	//---Vertical--- 
// 	dof=0; side=0; disV=100000;
// 	float Tan=tan(degToRad(ra));
// 		if(cos(degToRad(ra))> 0.001){ rx=(((int)px>>6)<<6)+64;      ry=(px-rx)*Tan+py; xo= 64; yo=-xo*Tan;}//looking left
// 	else if(cos(degToRad(ra))<-0.001){ rx=(((int)px>>6)<<6) -0.0001; ry=(px-rx)*Tan+py; xo=-64; yo=-xo*Tan;}//looking right
// 	else { rx=px; ry=py; dof=8;}                                                  //looking up or down. no hit  

// 	while(dof<8) 
// 	{ 
// 	mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;                     
// 	if(mp>0 && mp<mapX*mapY && map[mp]==1){ dof=8; disV=cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py);}//hit         
// 	else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
// 	} 
// 	vx=rx; vy=ry;

// 	//---Horizontal---
// 	dof=0; disH=100000;
// 	Tan=1.0/Tan; 
// 		if(sin(degToRad(ra))> 0.001){ ry=(((int)py>>6)<<6) -0.0001; rx=(py-ry)*Tan+px; yo=-64; xo=-yo*Tan;}//looking up 
// 	else if(sin(degToRad(ra))<-0.001){ ry=(((int)py>>6)<<6)+64;      rx=(py-ry)*Tan+px; yo= 64; xo=-yo*Tan;}//looking down
// 	else{ rx=px; ry=py; dof=8;}                                                   //looking straight left or right
	
// 	while(dof<8) 
// 	{ 
// 	mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;                          
// 	if(mp>0 && mp<mapX*mapY && map[mp]==1){ dof=8; disH=cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py);}//hit         
// 	else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
// 	} 
	
// 	glColor3f(0,0.8,0);
// 	if(disV<disH){ rx=vx; ry=vy; disH=disV; glColor3f(0,0.6,0);}                  //horizontal hit first
// 	glLineWidth(2); glBegin(GL_LINES); glVertex2i(px,py); glVertex2i(rx,ry); glEnd();//draw 2D ray
		
// 	int ca=FixAng(pa-ra); disH=disH*cos(degToRad(ca));                            //fix fisheye 
// 	int lineH = (mapS*320)/(disH); if(lineH>320){ lineH=320;}                     //line height and limit
// 	int lineOff = 160 - (lineH>>1);                                               //line offset
	
// 	glLineWidth(8);glBegin(GL_LINES);glVertex2i(r*8+530,lineOff);glVertex2i(r*8+530,lineOff+lineH);glEnd();//draw vertical wall  

// 	ra=FixAng(ra-1);                                                              //go to next ray
//  }
// }


void display(struct mlx_key_data keydata, void *game_data)
{
	keys_t key = keydata.key;
    t_data *data = (t_data *)game_data;

	//buttons
 	if(key == MLX_KEY_A)
	{ data->player->th+=5; data->player->th=FixAng(data->player->th); pdx=cos(deg2rad(data->player->th)); pdy=-sin(deg2rad(data->player->th));} 	
		if(key == MLX_KEY_D)
	{ data->player->th-=5; data->player->th=FixAng(data->player->th); pdx=cos(deg2rad(data->player->th)); pdy=-sin(deg2rad(data->player->th));} 
		if(key == MLX_KEY_W)
	{ data->player->x += pdx*5; data->player->y += pdy*5;}
		if(key == MLX_KEY_S)
	{ data->player->x -= pdx*5; data->player->y -= pdy*5;} 
	drawMap2D(data);
	printf("here1\n");
	// drawPlayer2D(data);
	printf("here2\n");
	// drawRays2D(data);
}