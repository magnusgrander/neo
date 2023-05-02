/* Copyright (C) 2023 Magnus Grander - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the BSD license.
 *
 * You should have received a copy of the BSD license with
 * this file. 
 */

#include "neo.h"

void SaveScreenshot()
{
    const Uint32 format = SDL_PIXELFORMAT_ARGB8888;
     
    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, 320, 200, 32, format);
    SDL_RenderReadPixels(renderer, NULL, format, surface->pixels, surface->pitch);
    SDL_SaveBMP(surface, "screenshot.bmp");
    SDL_FreeSurface(surface);
}

int main(int argc, char* argv[] )
{
	int             iFileHandle;
    bool            bLoadOk;
    int             iLoadSize;
    unsigned char   bNeoPic[32768];  
    int R[16];
    int G[16];
	int B[16];    
    int             iN;
    int             iPtr, iInk;
    int             iR, iG, iB;
    int             iX, iY, iZ;
    unsigned int    uW0, uW1, uW2, uW3;
    unsigned int    uBit;
    bool quit = false;    
    int i;
    
    if (argc != 2) {
		fprintf (stderr, "wrong number of arguments!\n");
		fprintf (stderr, "Usage: neo filename.neo\n");
		exit (1);
	}   
    
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(320, 200, 0, &window, &renderer);
       
            						
			FILE * filp = fopen(argv[1], "rb"); 
			iLoadSize = fread(bNeoPic, sizeof(char), 32768, filp);
                
            if (iLoadSize == 32128)
            {
                bLoadOk = true;

                // Skip two words (Flag byte=0, assume resolution=0)
                // Extract the palette from the next 16 words, and
                // convert into a temporary array of TColor:
                for (iN=0; iN<16; ++iN)
                {
                    iR = floor((bNeoPic[iN*2 + 4] & 0x07) * 255.0 / 7.0);
                    iG = floor((bNeoPic[iN*2 + 5] & 0x70) * 255.0 / 7.0 / 16.0);
                    iB = floor((bNeoPic[iN*2 + 5] & 0x07) * 255.0 / 7.0);

                    //colNeoPalette[iN] = TColor(RGB(iR, iG, iB));
					R[iN] = iR;
					G[iN] = iG;
					B[iN] = iB;                   
                }        

                // Address pointer, past 128b header:
                iPtr = 128;

                // 200 rows of image:
                for (iY=0; iY<200; ++iY)
                {
                    // 20 column blocks:
                    for (iX=0; iX<20; ++iX)
                    {
                        // Fetch the 4 words that make up the
                        // next 16 pixels across 4 bitplanes:
                        uW0 = bNeoPic[iPtr+0] * 256 + bNeoPic[iPtr+1];
                        uW1 = bNeoPic[iPtr+2] * 256 + bNeoPic[iPtr+3];
                        uW2 = bNeoPic[iPtr+4] * 256 + bNeoPic[iPtr+5];
                        uW3 = bNeoPic[iPtr+6] * 256 + bNeoPic[iPtr+7];

                        // The first pixel is found in the highest bit:
                        uBit = 0x8000;

                        // 16 pixels to process:
                        for (iZ=0; iZ<16; ++iZ)
                        {
                            // Work out the colour index:
                            iInk = 0;
                            if (uW0 & uBit) iInk += 1;
                            if (uW1 & uBit) iInk += 2;
                            if (uW2 & uBit) iInk += 4;
                            if (uW3 & uBit) iInk += 8;

                            // Plot a pixel of that Tcolor:
                            SDL_SetRenderDrawColor(renderer, R[iInk], G[iInk], B[iInk], 255);
                            SDL_RenderDrawPoint(renderer, iX*16 + iZ, iY );
                            SDL_RenderPresent(renderer);
                            //imgPic->Canvas->Pixels[iX*16 + iZ][iY] = colNeoPalette[iInk];

                            uBit >>= 1;
                        }
                        iPtr += 8;
                    }
              
				}
			}
			
		while (!quit)
		{
        SDL_WaitEvent(&event);
 
        switch (event.type)
        {
        case SDL_QUIT:
        quit = true;
        break;
        }
    }    
   SaveScreenshot();  
   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);
   SDL_Quit();
   return EXIT_SUCCESS;  							
}
