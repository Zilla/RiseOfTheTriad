/*
Copyright (C) 1994-1995 Apogee Software, Ltd.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/
#include "rt_def.h"
#include "watcom.h"
#include <malloc.h>
#include <stdio.h>
#include "compat_stdlib.h"
#include "compat_conio.h"
#include <string.h>
#include "modexlib.h"
#include "rt_util.h"
#include "rt_draw.h"
#include "rt_scale.h"
#include "_rt_scal.h"
#include "rt_sc_a.h"
#include "engine.h"
#include "w_wad.h"
#include "z_zone.h"
#include "lumpy.h"
#include "rt_main.h"
#include "rt_ted.h"
#include "rt_vid.h"
#include "rt_view.h"
#include "rt_playr.h"
//MED

/*
=============================================================================

                               GLOBALS

=============================================================================
*/

// Draw Column vars

int dc_texturemid;
int dc_iscale;
int dc_invscale;
int sprtopoffset;
int dc_yl;
int dc_yh;
//byte * dc_firstsource;
byte *dc_source;
int centeryclipped;
int transparentlevel = 0;

/*
==========================
=
= SetPlayerLightLevel
=
==========================
*/

void SetPlayerLightLevel(void)
{
   int i;
   int lv;
   int intercept;
   int height;

   whereami = 23;
   if (MISCVARS->GASON == 1)
   {
      shadingtable = greenmap + (MISCVARS->gasindex << 8);
      return;
   }

   if (fulllight || fog)
   {
      shadingtable = colormap + (1 << 12);
      return;
   }

   height = PLAYERHEIGHT;

   if (player->angle < FINEANGLES / 8 || player->angle > 7 * FINEANGLES / 8)
      intercept = (player->x >> 11) & 0x1c;
   else if (player->angle < 3 * FINEANGLES / 8)
      intercept = (player->y >> 11) & 0x1c;
   else if (player->angle < 5 * FINEANGLES / 8)
      intercept = (player->x >> 11) & 0x1c;
   else
      intercept = (player->y >> 11) & 0x1c;

   if (lightsource)
   {
      lv = (((LightSourceAt(player->x >> 16, player->y >> 16) >> intercept) & 0xf) >> 1);
      i = maxshade - (height >> normalshade) - lv;
      if (i < minshade)
         i = minshade;
      shadingtable = colormap + (i << 8);
   }
   else
   {
      i = maxshade - (height >> normalshade);
      if (i < minshade)
         i = minshade;
      shadingtable = colormap + (i << 8);
   }
}

/*
==========================
=
= SetLightLevel
=
==========================
*/

void SetLightLevel(int height)
{
   int i;

   whereami = 24;
   if (MISCVARS->GASON == 1)
   {
      shadingtable = greenmap + (MISCVARS->gasindex << 8);
      return;
   }

   if (fulllight)
   {
      shadingtable = colormap + (1 << 12);
      return;
   }
   if (fog)
   {
      i = (height >> normalshade) + minshade;
      if (i > maxshade)
         i = maxshade;
      shadingtable = colormap + (i << 8);
   }
   else
   {
      i = maxshade - (height >> normalshade);
      if (i < minshade)
         i = minshade;
      shadingtable = colormap + (i << 8);
   }
}

/*
==========================
=
= ScaleTransparentPost
=
==========================
*/
void ScaleTransparentPost(byte *src, byte *buf, int level)
{
   int offset;
   int length;
   int topscreen;
   int bottomscreen;
   byte *oldlevel;
   byte *seelevel;
#if (DEVELOPMENT == 1)
   boolean found = false;
   int i;
#endif

   whereami = 25;
#if (DEVELOPMENT == 1)
   if ((shadingtable >= colormap) && (shadingtable <= (colormap + (31 * 256))))
   {
      found = true;
   }
   else if ((shadingtable >= redmap) && (shadingtable <= (redmap + (31 * 256))))
   {
      found = true;
   }
   else
   {
      for (i = 0; i < MAXPLAYERCOLORS; i++)
      {
         if ((shadingtable >= playermaps[i]) || (shadingtable <= (playermaps[i] + (31 * 256))))
            found = true;
      }
   }
   if (found == false)
   {
      Error("Shadingtable out of range\n");
   }
   if ((level < 0) || (level >= 64))
   {
      Error("translucent level out of range\n");
   }
#endif

   seelevel = colormap + (((level + 64) >> 2) << 8);
   oldlevel = shadingtable;
   offset = *(src++);
   for (; offset != 255;)
   {
      length = *(src++);
      topscreen = sprtopoffset + (dc_invscale * offset);
      bottomscreen = topscreen + (dc_invscale * length);
      dc_yl = (topscreen + SFRACUNIT) >> SFRACBITS;
      dc_yh = ((bottomscreen - 1) >> SFRACBITS);
      if (dc_yh >= viewheight)
         dc_yh = viewheight - 1;
      if (dc_yl < 0)
         dc_yl = 0;
      if ((*src) == 254)
      {
         shadingtable = seelevel;
         if (dc_yl <= dc_yh)
            R_TransColumn(buf);
         src++;
         offset = *(src++);
         shadingtable = oldlevel;
      }
      else
      {
         if (dc_yl <= dc_yh)
         {
            dc_source = src - offset;
            R_DrawColumn(buf);
         }
         src += length;
         offset = *(src++);
      }
   }

   whereami = -2;
}

void ScaleMaskedPost(byte *src, byte *buf)
{
   int offset;
   int length;
   int topscreen;
   int bottomscreen;

   whereami = 26;
   offset = *(src++);
   for (; offset != 255;)
   {
      length = *(src++);
      topscreen = sprtopoffset + (dc_invscale * offset);
      bottomscreen = topscreen + (dc_invscale * length);
      dc_yl = (topscreen + SFRACUNIT) >> SFRACBITS;
      dc_yh = ((bottomscreen - 1) >> SFRACBITS);
      if (dc_yh >= viewheight)
         dc_yh = viewheight - 1;
      if (dc_yl < 0)
         dc_yl = 0;
      if (dc_yl <= dc_yh)
      {
         dc_source = src - offset;
         R_DrawColumn(buf);
#if (DEVELOPMENT == 1)
//         if (dc_firstsource<src)
//            SoftError("dc_firstsource=%p src=%p\n",dc_firstsource,src);
#endif
      }
      src += length;
      offset = *(src++);
   }
}

void ScaleClippedPost(byte *src, byte *buf)
{
   int offset;
   int length;
   int topscreen;
   int bottomscreen;

   whereami = 27;
   offset = *(src++);
   for (; offset != 255;)
   {
      length = *(src++);
      topscreen = sprtopoffset + (dc_invscale * offset);
      bottomscreen = topscreen + (dc_invscale * length);
      dc_yl = (topscreen + SFRACUNIT - 1) >> SFRACBITS;
      dc_yh = ((bottomscreen - 1) >> SFRACBITS);
      if (dc_yh >= viewheight)
         dc_yh = viewheight - 1;
      if (dc_yl < 0)
         dc_yl = 0;
      if (dc_yl <= dc_yh)
      {
         dc_source = src - offset;
         R_DrawClippedColumn(buf);
      }
      src += length;
      offset = *(src++);
   }
}

void ScaleSolidMaskedPost(int color, byte *src, byte *buf)
{
   int offset;
   int length;
   int topscreen;
   int bottomscreen;

   whereami = 28;
   offset = *(src++);
   for (; offset != 255;)
   {
      length = *(src++);
      topscreen = sprtopoffset + (dc_invscale * offset);
      bottomscreen = topscreen + (dc_invscale * length);
      dc_yl = (topscreen + SFRACUNIT) >> SFRACBITS;
      dc_yh = ((bottomscreen - 1) >> SFRACBITS);
      if (dc_yh >= viewheight)
         dc_yh = viewheight - 1;
      if (dc_yl < 0)
         dc_yl = 0;
      if (dc_yl <= dc_yh)
      {
         dc_source = src - offset;
         R_DrawSolidColumn(color, buf);
      }
      src += length;
      offset = *(src++);
   }
}

void ScaleTransparentClippedPost(byte *src, byte *buf, int level)
{
   int offset;
   int length;
   int topscreen;
   int bottomscreen;
   byte *oldlevel;
   byte *seelevel;

   whereami = 29;

   seelevel = colormap + (((level + 64) >> 2) << 8);
   oldlevel = shadingtable;
   offset = *(src++);
   for (; offset != 255;)
   {
      length = *(src++);
      topscreen = sprtopoffset + (dc_invscale * offset);
      bottomscreen = topscreen + (dc_invscale * length);
      dc_yl = (topscreen + SFRACUNIT) >> SFRACBITS;
      dc_yh = ((bottomscreen - 1) >> SFRACBITS);
      if (dc_yh >= viewheight)
         dc_yh = viewheight - 1;
      if (dc_yl < 0)
         dc_yl = 0;
      if ((*src) == 254)
      {
         shadingtable = seelevel;
         if (dc_yl <= dc_yh)
            R_TransColumn(buf);
         src++;
         offset = *(src++);
         shadingtable = oldlevel;
      }
      else
      {
         if (dc_yl <= dc_yh)
         {
            dc_source = src - offset;
            R_DrawClippedColumn(buf);
         }
         src += length;
         offset = *(src++);
      }
   }
}

void ScaleMaskedWidePost(byte *src, byte *buf, int x, int width)
{
   int ofs;
   int msk;

   whereami = 30;
   buf += x >> 2;
   ofs = ((x & 3) << 3) + (x & 3) + width - 1;
   VGAMAPMASK(*((byte *)mapmasks1 + ofs));
   ScaleMaskedPost(src, buf);
   msk = (byte) * ((byte *)mapmasks2 + ofs);
   if (msk == 0)
      return;
   buf++;
   VGAMAPMASK(msk);
   ScaleMaskedPost(src, buf);
   msk = (byte) * ((byte *)mapmasks3 + ofs);
   if (msk == 0)
      return;
   buf++;
   VGAMAPMASK(msk);
   ScaleMaskedPost(src, buf);
}

void ScaleClippedWidePost(byte *src, byte *buf, int x, int width)
{
   int ofs;
   int msk;

   whereami = 31;
   buf += x >> 2;
   ofs = ((x & 3) << 3) + (x & 3) + width - 1;
   VGAMAPMASK(*((byte *)mapmasks1 + ofs));
   ScaleClippedPost(src, buf);
   msk = (byte) * ((byte *)mapmasks2 + ofs);
   if (msk == 0)
      return;
   buf++;
   VGAMAPMASK(msk);
   ScaleClippedPost(src, buf);
   msk = (byte) * ((byte *)mapmasks3 + ofs);
   if (msk == 0)
      return;
   buf++;
   VGAMAPMASK(msk);
   ScaleClippedPost(src, buf);
}

/*
=======================
=
= ScaleShape
=
=======================
*/

void ScaleShape(visobj_t *sprite)
{
   byte *shape;
   int frac;
   patch_t *p;
   int x1, x2;
   int tx;
   int size;
   int plane;

   whereami = 32;
   shape = W_CacheLumpNum(sprite->shapenum, PU_CACHE);
   p = (patch_t *)shape;
   size = p->origsize >> 7;
   //   sprite->viewheight<<=1;
   dc_invscale = sprite->viewheight << ((10 - HEIGHTFRACTION) - size);
   tx = -p->leftoffset;
   sprite->viewx = (sprite->viewx << SFRACBITS) - (sprite->viewheight << (SFRACBITS - HEIGHTFRACTION - 1)) + (SFRACUNIT >> 1);
   //
   // calculate edges of the shape
   //
   x1 = (sprite->viewx + (tx * dc_invscale)) >> SFRACBITS;
   if (x1 >= viewwidth)
   {
      return; // off the right side
   }
   tx += p->width;
   x2 = ((sprite->viewx + (tx * dc_invscale)) >> SFRACBITS) - 1;
   if (x2 < 0)
   {
      return; // off the left side
   }

   // dc_iscale=(1<<(16+6+HEIGHTFRACTION+size))/sprite->viewheight;
   dc_iscale = 0xffffffffu / (unsigned)dc_invscale;
   dc_texturemid = (((sprite->h1 << size) + p->topoffset) << SFRACBITS); //+(SFRACUNIT>>1);
   sprtopoffset = centeryfrac - FixedMul(dc_texturemid, dc_invscale);
   shadingtable = sprite->colormap;

   if (x1 < 0)
   {
      frac = dc_iscale * (-x1);
      x1 = 0;
   }
   else
      frac = 0;
   x2 = x2 >= viewwidth ? viewwidth - 1 : x2;

   if (sprite->viewheight > ((1 << (HEIGHTFRACTION + 6)) << size))
   {
      int texturecolumn;
      int lastcolumn;
      int startx;
      int width;

      width = 1;
      startx = 0;
      lastcolumn = -1;
      for (; x1 <= x2; x1++, frac += dc_iscale)
      {
         if (posts[x1].wallheight > sprite->viewheight)
         {
            if (lastcolumn >= 0)
            {
               ScaleMaskedWidePost(((p->collumnofs[lastcolumn]) + shape), (byte *)bufferofs, startx, width);
               width = 1;
               lastcolumn = -1;
            }
            continue;
         }
         texturecolumn = frac >> SFRACBITS;
         if ((texturecolumn == lastcolumn) && (width < 9))
         {
            width++;
            continue;
         }
         else
         {
            if (lastcolumn >= 0)
            {
               ScaleMaskedWidePost(((p->collumnofs[lastcolumn]) + shape), (byte *)bufferofs, startx, width);
               width = 1;
               startx = x1;
               lastcolumn = texturecolumn;
            }
            else
            {
               startx = x1;
               lastcolumn = texturecolumn;
            }
         }
      }
      if (lastcolumn != -1)
         ScaleMaskedWidePost(((p->collumnofs[lastcolumn]) + shape), (byte *)bufferofs, startx, width);
   }
   else
   {
      byte *b;
      int startfrac;
      int startx;

      startx = x1;
      startfrac = frac;
      if (doublestep > 1)
      {
         for (plane = startx; plane < startx + 4; plane += 2, startfrac += (dc_iscale << 1))
         {
            frac = startfrac;
            //   VGAWRITEMAP(plane&3);
            for (x1 = plane; x1 <= x2; x1 += 4, frac += (dc_iscale << 2))
            {
               if (
                   (posts[x1].wallheight > sprite->viewheight) &&
                   (posts[x1 + 1].wallheight > sprite->viewheight))
                  continue;
               if (x1 == viewwidth - 1)
                  ScaleMaskedWidePost(((p->collumnofs[frac >> SFRACBITS]) + shape), (byte *)bufferofs, x1, 1);
               else
                  ScaleMaskedWidePost(((p->collumnofs[frac >> SFRACBITS]) + shape), (byte *)bufferofs, x1, 2);
            }
         }
      }
      else
      {
         for (plane = startx; plane < startx + 4; plane++, startfrac += dc_iscale)
         {
            frac = startfrac;
            b = (byte *)bufferofs + (plane >> 2);
            VGAWRITEMAP(plane & 3);
            for (x1 = plane; x1 <= x2; x1 += 4, frac += (dc_iscale << 2), b++)
            {
               if (posts[x1].wallheight > sprite->viewheight)
                  continue;
               ScaleMaskedPost(((p->collumnofs[frac >> SFRACBITS]) + shape), b);
            }
         }
      }
   }
}

/*
=======================
=
= ScaleTranparentShape
=
=======================
*/

void ScaleTransparentShape(visobj_t *sprite)
{
   byte *shape;
   int frac;
   transpatch_t *p;
   int x1, x2;
   int tx;
   int size;
   byte *b;
   int startfrac;
   int startx;
   int plane;

   whereami = 33;
   shape = W_CacheLumpNum(sprite->shapenum, PU_CACHE);
   p = (transpatch_t *)shape;
   size = p->origsize >> 7;
   dc_invscale = sprite->viewheight << ((10 - HEIGHTFRACTION) - size);
   tx = -p->leftoffset;
   sprite->viewx = (sprite->viewx << SFRACBITS) - (sprite->viewheight << (SFRACBITS - HEIGHTFRACTION - 1));
   //
   // calculate edges of the shape
   //
   x1 = (sprite->viewx + (tx * dc_invscale)) >> SFRACBITS;
   if (x1 >= viewwidth)
   {
      return; // off the right side
   }
   tx += p->width;
   x2 = ((sprite->viewx + (tx * dc_invscale)) >> SFRACBITS) - 1;
   if (x2 < 0)
   {
      return; // off the left side
   }

   //   dc_iscale=(1<<(16+6+HEIGHTFRACTION+size))/sprite->viewheight;
   dc_iscale = 0xffffffffu / (unsigned)dc_invscale;
   dc_texturemid = (((sprite->h1 << size) + p->topoffset) << SFRACBITS); //+(SFRACUNIT>>1);
   sprtopoffset = centeryfrac - FixedMul(dc_texturemid, dc_invscale);
   shadingtable = sprite->colormap;

   if (x1 < 0)
   {
      frac = dc_iscale * (-x1);
      x1 = 0;
   }
   else
      frac = 0;
   x2 = x2 >= viewwidth ? viewwidth - 1 : x2;

#if 0
   for (; x1<=x2 ; x1++, frac += dc_iscale)
      {
      if (posts[x1].wallheight>sprite->viewheight)
         continue;
      VGAWRITEMAP(x1&3);
      VGAREADMAP(x1&3);
      ScaleTransparentPost(((p->collumnofs[frac>>SFRACBITS])+shape),(byte *)bufferofs+(x1>>2),sprite->h2);
      }
#endif
   startx = x1;
   startfrac = frac;

   for (plane = startx; plane < startx + 4; plane++, startfrac += dc_iscale)
   {
      frac = startfrac;
      b = (byte *)bufferofs + (plane >> 2);
      VGAWRITEMAP(plane & 3);
      VGAREADMAP(plane & 3);
      for (x1 = plane; x1 <= x2; x1 += 4, frac += (dc_iscale << 2), b++)
      {
         if (posts[x1].wallheight > sprite->viewheight)
            continue;
         ScaleTransparentPost(((p->collumnofs[frac >> SFRACBITS]) + shape), b, sprite->h2);
      }
   }
}

/*
=======================
=
= ScaleSolidShape
=
=======================
*/

void ScaleSolidShape(visobj_t *sprite)
{
   byte *shape;
   int frac;
   patch_t *p;
   int x1, x2;
   int tx;
   int size;
   int plane;
   byte *b;
   int startfrac;
   int startx;

   whereami = 34;
   shape = W_CacheLumpNum(sprite->shapenum, PU_CACHE);
   p = (patch_t *)shape;
   size = p->origsize >> 7;
   dc_invscale = sprite->viewheight << ((10 - HEIGHTFRACTION) - size);
   tx = -p->leftoffset;
   sprite->viewx = (sprite->viewx << SFRACBITS) - (sprite->viewheight << (SFRACBITS - HEIGHTFRACTION - 1)) + (SFRACUNIT >> 1);
   //
   // calculate edges of the shape
   //
   x1 = (sprite->viewx + (tx * dc_invscale)) >> SFRACBITS;
   if (x1 >= viewwidth)
   {
      return; // off the right side
   }
   tx += p->width;
   x2 = ((sprite->viewx + (tx * dc_invscale)) >> SFRACBITS) - 1;
   if (x2 < 0)
   {
      return; // off the left side
   }

   //   dc_iscale=(1<<(16+6+HEIGHTFRACTION+size))/sprite->viewheight;
   dc_iscale = 0xffffffffu / (unsigned)dc_invscale;
   dc_texturemid = (((sprite->h1 << size) + p->topoffset) << SFRACBITS); //+(SFRACUNIT>>1);
   sprtopoffset = centeryfrac - FixedMul(dc_texturemid, dc_invscale);
   shadingtable = sprite->colormap;

   if (x1 < 0)
   {
      frac = dc_iscale * (-x1);
      x1 = 0;
   }
   else
      frac = 0;
   x2 = x2 >= viewwidth ? viewwidth - 1 : x2;

   startx = x1;
   startfrac = frac;
   for (plane = startx; plane < startx + 4; plane++, startfrac += dc_iscale)
   {
      frac = startfrac;
      b = (byte *)bufferofs + (plane >> 2);
      VGAWRITEMAP(plane & 3);
      for (x1 = plane; x1 <= x2; x1 += 4, frac += (dc_iscale << 2), b++)
      {
         if (posts[x1].wallheight > sprite->viewheight)
            continue;
         ScaleSolidMaskedPost(sprite->h2, ((p->collumnofs[frac >> SFRACBITS]) + shape), b);
      }
   }
}

/*
=======================
=
= ScaleWeapon
=
=======================
*/

void ScaleWeapon(int xoff, int y, int shapenum)
{
   byte *shape;
   int frac;
   int h;
   patch_t *p;
   int x1, x2;
   int tx;
   int xcent;
   byte *b;
   int startfrac;
   int startx;
   int plane;

   whereami = 35;
   SetPlayerLightLevel();
   shape = W_CacheLumpNum(shapenum, PU_CACHE);
   p = (patch_t *)shape;
   h = ((p->origsize * weaponscale) >> 17);
   centeryclipped = (viewheight - h) + FixedMul(y, weaponscale);
   xcent = centerx + FixedMul(xoff, weaponscale);
   dc_invscale = (h << 17) / p->origsize;

   tx = -p->leftoffset;
   xcent = (xcent << SFRACBITS) - (h << SFRACBITS);
   //
   // calculate edges of the shape
   //
   x1 = (xcent + (tx * dc_invscale)) >> SFRACBITS;
   if (x1 >= viewwidth)
      return; // off the right side
   tx += p->width;
   x2 = ((xcent + (tx * dc_invscale)) >> SFRACBITS) - 1;
   if (x2 < 0)
      return; // off the left side

   dc_iscale = 0xffffffffu / (unsigned)dc_invscale;
   dc_texturemid = (((p->origsize >> 1) + p->topoffset) << SFRACBITS) + (SFRACUNIT >> 1);
   sprtopoffset = (centeryclipped << 16) - FixedMul(dc_texturemid, dc_invscale);

   //
   // store information in a vissprite
   //
   if (x1 < 0)
   {
      frac = dc_iscale * (-x1);
      x1 = 0;
   }
   else
      frac = 0;

   x2 = x2 >= viewwidth ? viewwidth - 1 : x2;

   startx = x1;
   startfrac = frac;
   for (plane = startx; plane < startx + 4; plane++, startfrac += dc_iscale)
   {
      frac = startfrac;
      b = (byte *)bufferofs + (plane >> 2);
      VGAWRITEMAP(plane & 3);
      for (x1 = plane; x1 <= x2; x1 += 4, frac += dc_iscale << 2, b++)
         ScaleClippedPost(((p->collumnofs[frac >> SFRACBITS]) + shape), b);
   }
}

/*
=======================
=
= DrawUnScaledSprite
=
=======================
*/

void DrawUnScaledSprite(int x, int y, int shapenum, int shade)
{
   byte *shape;
   int frac;
   patch_t *p;
   int x1, x2;
   int tx;
   int xcent;
   byte *b;
   int startfrac;
   int startx;
   int plane;

   whereami = 36;
   shadingtable = colormap + (shade << 8);
   centeryclipped = y;
   xcent = x;
   shape = W_CacheLumpNum(shapenum, PU_CACHE);
   p = (patch_t *)shape;
   dc_invscale = 0x10000;

   tx = -p->leftoffset;
   xcent -= p->origsize >> 1;
   //
   // calculate edges of the shape
   //
   x1 = xcent + tx;
   if (x1 >= viewwidth)
      return; // off the right side
   tx += p->width;
   x2 = xcent + tx - 1;
   if (x2 < 0)
      return; // off the left side

   dc_iscale = 0x10000;
   dc_texturemid = (((p->height >> 1) + p->topoffset) << SFRACBITS); //+(SFRACUNIT>>1);
   sprtopoffset = (centeryclipped << 16) - dc_texturemid;

   //
   // store information in a vissprite
   //
   if (x1 < 0)
   {
      frac = dc_iscale * (-x1);
      x1 = 0;
   }
   else
      frac = 0;

   x2 = x2 >= viewwidth ? viewwidth - 1 : x2;

   startx = x1;
   startfrac = frac;
   for (plane = startx; plane < startx + 4; plane++, startfrac += dc_iscale)
   {
      frac = startfrac;
      b = (byte *)bufferofs + (plane >> 2);
      VGAWRITEMAP(plane & 3);
      for (x1 = plane; x1 <= x2; x1 += 4, frac += dc_iscale << 2, b++)
         ScaleClippedPost(((p->collumnofs[frac >> SFRACBITS]) + shape), b);
   }
}

/*
=======================
=
= DrawScreenSprite
=
=======================
*/

void DrawScreenSprite(int x, int y, int shapenum)
{
   whereami = 37;
   ScaleWeapon(x - 160, y - 200, shapenum);
}

/*
=======================
=
= DrawPositionedScaledSprite
=
=======================
*/

void DrawPositionedScaledSprite(int x, int y, int shapenum, int height, int type)
{
   byte *shape;
   int frac;
   patch_t *p;
   transpatch_t *tp;
   int x1, x2;
   int tx;
   int xcent;
   byte *b;
   int startfrac;
   int startx;
   int plane;
   int size;

   whereami = 38;
   shadingtable = colormap + (1 << 12);
   centeryclipped = y;
   xcent = x;
   shape = W_CacheLumpNum(shapenum, PU_CACHE);
   p = (patch_t *)shape;
   tp = (transpatch_t *)shape;

   size = p->origsize >> 7;
   dc_invscale = height << (10 - size);

   tx = -p->leftoffset;
   xcent = (xcent << SFRACBITS) - (height << (SFRACBITS - 1));

   //
   // calculate edges of the shape
   //
   x1 = (xcent + (tx * dc_invscale)) >> SFRACBITS;
   if (x1 >= viewwidth)
      return; // off the right side
   tx += p->width;
   x2 = ((xcent + (tx * dc_invscale)) >> SFRACBITS) - 1;
   if (x2 < 0)
      return; // off the left side

   dc_iscale = 0xffffffffu / (unsigned)dc_invscale;
   //   dc_iscale=(1<<(16+6+size))/height;
   dc_texturemid = (((32 << size) + p->topoffset) << SFRACBITS) + (SFRACUNIT >> 1);
   sprtopoffset = (centeryclipped << 16) - FixedMul(dc_texturemid, dc_invscale);

   //
   // store information in a vissprite
   //
   if (x1 < 0)
   {
      frac = dc_iscale * (-x1);
      x1 = 0;
   }
   else
      frac = 0;

   x2 = x2 >= viewwidth ? viewwidth - 1 : x2;

   startx = x1;
   startfrac = frac;
   for (plane = startx; plane < startx + 4; plane++, startfrac += dc_iscale)
   {
      frac = startfrac;
      b = (byte *)bufferofs + (plane >> 2);
      VGAWRITEMAP(plane & 3);
      VGAREADMAP(plane & 3);
      for (x1 = plane; x1 <= x2; x1 += 4, frac += dc_iscale << 2, b++)
         if (type == 0)
            ScaleClippedPost(((p->collumnofs[frac >> SFRACBITS]) + shape), b);
         else
            ScaleTransparentClippedPost(((tp->collumnofs[frac >> SFRACBITS]) + shape), b, transparentlevel);
   }
}

/*
=================
=
= DrawScreenSizedSprite
=
=================
*/
void DrawScreenSizedSprite(int lump)
{
   byte *shape;
   int frac;
   patch_t *p;
   int x1, x2;
   int tx;
   int plane;
   byte *b;
   int startfrac;

   whereami = 39;
   shadingtable = colormap + (1 << 12);
   shape = W_CacheLumpNum(lump, PU_CACHE);
   p = (patch_t *)shape;
   dc_invscale = (viewwidth << 16) / p->origsize;
   tx = -p->leftoffset;
   centeryclipped = viewheight >> 1;
   //
   // calculate edges of the shape
   //
   x1 = (tx * dc_invscale) >> SFRACBITS;
   if (x1 >= viewwidth)
   {
      return; // off the right side
   }
   tx += p->width;
   x2 = ((tx * dc_invscale) >> SFRACBITS) - 1;
   if (x2 < 0)
   {
      return; // off the left side
   }

   dc_iscale = 0xffffffffu / (unsigned)dc_invscale;
   dc_texturemid = (((p->origsize >> 1) + p->topoffset) << SFRACBITS) + (SFRACUNIT >> 1);
   sprtopoffset = (centeryclipped << 16) - FixedMul(dc_texturemid, dc_invscale);

   x2 = (viewwidth - 1);

   startfrac = 0;
   for (plane = 0; plane < 4; plane++, startfrac += dc_iscale)
   {
      frac = startfrac;
      b = (byte *)bufferofs + (plane >> 2);
      VGAWRITEMAP(plane & 3);
      for (x1 = plane; x1 <= x2; x1 += 4, frac += (dc_iscale << 2), b++)
      {
         ScaleClippedPost(((p->collumnofs[frac >> SFRACBITS]) + shape), b);
      }
   }
}

#if 0
   byte *shape;
   int      frac;
   patch_t *p;
   int      x1,x2;
   int      tx;
   int      xdc_invscale;
   int      xdc_iscale;
   byte *   buf;
   byte *   b;
   int      plane;
   int      startx,startfrac;

   whereami=39;
   SetPlayerLightLevel();
   buf=(byte *)bufferofs;
   shape=W_CacheLumpNum(lump,PU_CACHE);
   p=(patch_t *)shape;
   dc_invscale=(viewheight<<16)/200;
	xdc_invscale=(viewwidth<<16)/320;

   tx=-p->leftoffset;
   centeryclipped=viewheight>>1;
//
// calculate edges of the shape
//
        x1 = (tx*xdc_invscale)>>SFRACBITS;
        if (x1 >= viewwidth)
                return;               // off the right side
        tx+=p->width;
        x2 = ((tx*xdc_invscale)>>SFRACBITS) - 1 ;
		  if (x2 < 0)
                return;         // off the left side

   dc_iscale=(200*65536)/viewheight;
   xdc_iscale=(320*65536)/viewwidth;
   dc_texturemid=(((p->height>>1)+p->topoffset)<<SFRACBITS)+(SFRACUNIT>>1);
   sprtopoffset=(centeryclipped<<16) - FixedMul(dc_texturemid,dc_invscale);

//
// store information in a vissprite
//
   if (x1<0)
      {
      frac=xdc_iscale*(-x1);
      x1=0;
      }
   else
      frac=0;
        x2 = x2 >= viewwidth ? viewwidth-1 : x2;

   startx=x1;
   startfrac=frac;
   for (plane=startx;plane<startx+4;plane++,startfrac+=xdc_iscale)
      {
      frac=startfrac;
      b=(byte *)bufferofs+(plane>>2);
      VGAWRITEMAP(plane&3);
      for (x1=plane; x1<=x2 ; x1+=4, frac += xdc_iscale<<2,b++)
         ScaleClippedPost(((p->collumnofs[frac>>SFRACBITS])+shape),b);
      }
}
#endif

//******************************************************************************
//
// DrawNormalPost
//
//******************************************************************************

void DrawNormalPost(byte *src, byte *buf)
{
   int offset;
   int length;
   int s;

   whereami = 40;

   while (1)
   {
      offset = *(src++);
      if (offset == 0xff)
         return;
      else
      {
         length = *(src++);
         for (s = 0; s < length; s++)
            *(buf + ylookup[offset + s]) = *(src + s);
         src += length;
      }
   }
}

//******************************************************************************
//
// DrawNormalSprite
//
//******************************************************************************

void DrawNormalSprite(int x, int y, int shapenum)
{
   byte *buffer;
   int cnt;
   byte *shape;
   patch_t *p;
   int plane;
   byte *b;
   int startx;

   whereami = 41;

   shape = W_CacheLumpNum(shapenum, PU_CACHE);
   p = (patch_t *)shape;

   if (((x - p->leftoffset) < 0) || ((x - p->leftoffset + p->width) > 320))
      Error("DrawNormalSprite: x is out of range x=%ld\n", x - p->leftoffset + p->width);
   if (((y - p->topoffset) < 0) || ((y - p->topoffset + p->height) > 200))
      Error("DrawNormalSprite: y is out of range y=%ld\n", y - p->topoffset + p->height);

   startx = x - p->leftoffset;
   buffer = (byte *)bufferofs + ylookup[y - p->topoffset];

   for (plane = startx; plane < startx + 4; plane++)
   {
      b = buffer + (plane >> 2);
      VGAWRITEMAP(plane & 3);
      for (cnt = plane - startx; cnt < p->width; cnt += 4, b++)
         DrawNormalPost((byte *)(p->collumnofs[cnt] + shape), b);
   }
}
