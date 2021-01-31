/*
 * renderer.h
 *
 *  Created on: Nov 27, 2010
 *      Author: johnz
 */

#ifndef RENDERER_H_
#define RENDERER_H_

void renderHomeScreen(void);
void updateHomeScreen(float voltage, float lumens, float percentRange);
void renderSimpleScreen(void);
void renderGraphScreen(unsigned char domain, int pageIncrement);

#endif /* RENDERER_H_ */
