/*
 * animation.h
 *
 * Created: 27.07.2014 15:20:24
 *  Author: Richi
 */ 

#ifndef ANIMATION_H_
#define ANIMATION_H_

#define NUM(a) (sizeof(a) / sizeof((*a)))

typedef uint8_t (*funcPtrProgram[])(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time);

void cube_play_animation(cube *data);

void cube_clear(cube *data);
uint8_t cube_animation_control(uint8_t *index, uint8_t *tmp, uint8_t top, uint8_t chang);

#endif /* ANIMATION_H_ */