#ifndef _RENDER_H
#define _RENDER_H

#define LOOK_INVISIBLE  0x00
#define LOOK_COLOR      0x01
#define LOOK_SPRITE     0x02

typedef struct  // Something look
{
	int flags;
	union {
		Texture2D  sprite;
		Color      color;
	} as;
	Color tint;      // if as sprite
} Looks;

#endif /* _RENDER_H */
