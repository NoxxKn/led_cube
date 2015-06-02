/*
 * animaiton.c
 *
 * Created: 27.07.2014 15:17:38
 *  Author: Richi
 */ 

#include <avr/io.h>
#include <include/ascii.h>
#include <include/tlc.h>
#include <avr/pgmspace.h>
#include <include/animation.h>
#include <stdlib.h>
#include <string.h>

extern uint8_t timer2_count;

static uint8_t cube_layer_shift_front_back(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time);
static uint8_t cube_layer_shift_left_right(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time);
static uint8_t cube_layer_shift_top_bottom(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time);
static uint8_t cube_rocket_explode(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time);
static uint8_t cube_expand_1(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time);
static uint8_t cube_expand_2(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time);
static uint8_t cube_expand_3(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time);
static uint8_t cube_expand_4(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time);
static uint8_t cube_explosion(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time);
static uint8_t cube_sine_wave_side(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time);
static uint8_t cube_sine_wave_diagonal(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time);
static uint8_t cube_font_out(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time);
static uint8_t cube_message_board(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time);
static uint8_t cube_put_string(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time);
static uint8_t clube_layer_rand(cube *data, uint8_t *index);
static uint8_t cube_lift(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time);
static uint8_t cube_line_down(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time);
static uint8_t cube_slidesidewards(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time);
static uint8_t cube_slidebackwards(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time);
static uint8_t cube_rain(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time);

const funcPtrProgram animation_func = {
    cube_expand_1,
    cube_expand_2,
    cube_expand_3,
    cube_expand_4,
    cube_layer_shift_front_back,
    cube_layer_shift_left_right,
    cube_layer_shift_top_bottom,
    cube_rocket_explode,
    cube_sine_wave_side,
    cube_sine_wave_diagonal,
    //cube_message_board,
    //cube_put_string,
	//cube_slidebackwards,
	//cube_slidesidewards,
	//cube_lift,
    //cube_line_down,
    cube_rain
};

static uint8_t animation_stats = 0; // Highest bit shows global usage state of 1 = in use and 0 = not in use.
                                    // If function returns 1 to jump to another one the bit must be cleared else an error occur.

static uint8_t animation_prog = 0;         // Stores the actual program which is shown.
static uint8_t animation_tmp = 0;          // Stores data from an animation.
static uint8_t animation_count = 0;        // Stores internal counter.
static uint8_t animation_time = 40;        // Holds the actual time for animation flow.

const uint8_t sine_wave[10] = {0x30, 0x40, 0x80, 0x40, 0x30, 0x0C, 0x02, 0x01,  0x02, 0x0C};

const uint8_t animation_counts = NUM(animation_func);

inline void cube_play_animation(cube *data)
{
    if (timer2_count >= animation_time) {
        timer2_count = 0;
        if (animation_prog < animation_counts) {
            animation_prog += animation_func[animation_prog](data, &animation_count, &animation_tmp, &animation_time);
        }
        else {
            animation_prog = 0;
            timer2_count = 40;
        }
    }
}

uint8_t cube_line_down(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time)
{
    static uint8_t mov = 0;
    uint8_t i;

    if ((*index)++ % 2 == 0)
    {
        do
        {
            *tmp = rand() % 5;
        } while(*tmp == mov || *tmp == 0);
        mov = *tmp;
    }

    for (i = 0; i < 7; i++)
    {
        memcpy(&(data->layer_f[i]), &(data->layer_f[i+1]), sizeof(uint64_t));
    }
    switch(*tmp)
    {
        case 0: //standstill
        break;
        case 1: //right
            for (i = 0; i < 7; i++)
            {
                if (data->layer_d[7].row[i] != 0 && data->layer_d[7].row[i] != 0x80)
                {
                    data->layer_d[7].row[i] <<= 1;
                }
            }
            break;
        case 2: //forward
            if (data->layer_d[7].row[0] == 0)
            {
                for (i = 0; i < 7; i++)
                {
                    data->layer_d[7].row[i] = data->layer_d[7].row[i+1];
                    data->layer_d[7].row[i+1] = 0;
                }
            }
            break;
        case 3: //backward
            if (data->layer_d[7].row[7] == 0)
            {
                for (i = 7; (int8_t)i > 0; i--)
                {
                    data->layer_d[7].row[i] = data->layer_d[7].row[i-1];
                    data->layer_d[7].row[i-1] = 0;
                }
            }
            break;
        case 4: //left
            for (i = 0; i < 7; i++)
            {
                if (data->layer_d[7].row[i] != 0 && data->layer_d[7].row[i] != 0x01)
                {
                    data->layer_d[7].row[i] >>= 1;
                }
            }
            break;
    }
    *tmp = 0;
    return 0;
}

uint8_t cube_rain(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time)
{
    int8_t i;
    uint64_t led;

    for (i = 0; i < 7; i++)
    {
        memcpy(&(data->layer_f[i]), &(data->layer_f[i+1]), sizeof(uint64_t));
    }
    i = 8;
    data->layer_f[7] = 0;
    while(i-- > 0)
    {
        led = 1;
        led <<= rand() % 64;
        data->layer_f[7] |= led;
    }

    return 0;
}

uint8_t cube_put_string(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time)
{
    uint8_t ch;
    
    ch = pgm_read_byte(&string[*index]) - 32;
    if ((*tmp)++ < 5) {
        cube_font_out(data, &ch, tmp, 0);
    }
    else {
		ch = 0;
        cube_font_out(data, &ch, tmp, 0);
		if(*tmp >= 8) {
            *tmp = 0;
            if (pgm_read_byte(&string[++(*index)]) == 0) {
                *index = 0;
            }
        }
    }
    return 0;
}

uint8_t cube_font_out(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time)
{
    uint8_t j;
    
    //cube_clear(data);
    cube_message_board(data, index, tmp, time);

    for(j = 0; j < 7; j++) {
        if ((1 << (5-*tmp)) & pgm_read_byte(&font8x8[*index][j])) {
            data->layer_d[7-j].row[0] = 0x80;
        }
    }

    return 0;//cube_animation_control(index, tmp, 100, 100);
}

uint8_t cube_message_board(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time)
{
    uint8_t i, k, l;
    cube tmp2;

    memcpy(&tmp2, data, sizeof(cube));

    cube_clear(data);

    for (i = 0; i  < 8; i++)
    {
        for (k = 0, l = 7; k < 7; k++, l--) {
            data->layer_d[i].row[k + 1] |= tmp2.layer_d[i].row[k] & 0x80;
            data->layer_d[i].row[l - 1] |= tmp2.layer_d[i].row[l] & 0x01;
        }
        //data->layer_d[i].row[0] |= tmp2.layer_d[i].row[0] << 1;
        data->layer_d[i].row[7] |= tmp2.layer_d[i].row[7] >> 1;
    }
    return 0;
}

uint8_t cube_sine_wave_side(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time)
{
    uint8_t i, j;

    cube_clear(data);

    for(j = 0; j < 8; j++) {
        for(i = 0; i < 8; i++) {
            if ((1 << i) & sine_wave[(j  + *tmp) % (sizeof(sine_wave) / sizeof(uint8_t))]) {
                data->layer_d[i].row[j] = 0xFF;
            }
        }
    }

    return cube_animation_control(index, tmp, 50, 50);;
}

uint8_t cube_sine_wave_diagonal(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time)
{
    uint8_t i, j, k;

    cube_clear(data);

    for(j = 0; j < 8; j++) {
        for(i = 0; i < 8; i++) {
            for(k = 0; k < 8; k++)
            {
                if ((1 << i) & sine_wave[(j + k + *tmp) % (sizeof(sine_wave) / sizeof(uint8_t))]) {
                    data->layer_d[i].row[j] |= (1 << k);
                }
            }
        }
    }

    return cube_animation_control(index, tmp, 50, 50);;
}

uint8_t cube_layer_shift_front_back(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time)
{
    uint8_t model = 0x01;
    uint8_t i, j;

    cube_clear(data);

    model <<= *tmp;

    for(j = 0; j < 8; j++) {
        for(i = 0; i < 8; i++) {
            data->layer_d[i].row[j] = model;
        }
    }

    return cube_animation_control(index, tmp, 15, 7);
}

uint8_t cube_layer_shift_top_bottom(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time)
{
    uint8_t model = 0xFF;
    uint8_t i;

    cube_clear(data);

    for(i = 0; i < 8; i++) {
        data->layer_d[*tmp].row[i] = model;
    }

    return cube_animation_control(index, tmp, 15, 7);
}

uint8_t cube_layer_shift_left_right(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time)
{
    uint8_t model = 0xFF;
    uint8_t i;

    cube_clear(data);
    for(i = 0; i < 8; i++) {
        data->layer_d[i].row[*tmp] = model;
    }

    return cube_animation_control(index, tmp, 15, 7);
}

uint8_t cube_explosion(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time)
{
    uint8_t i, j;
    
    cube_clear(data);

    for(i = 0; i < 8; i++) {
        for(j = 0; j < 8; j++) {
            data->layer_d[i].row[j] = rand();
        }
    }
    return 1;
}

uint8_t cube_rocket_explode(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time)
{
    cube_clear(data);

    switch(*index) {
        case 0:
        data->layer_d[*index].row[3] = 0x10;
        break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        data->layer_d[*index - 1].row[3] = 0x10;
        data->layer_d[*index].row[3] = 0x10;
        break;
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        clube_layer_rand(data, index);
        //change time
        break;
        default:
        //maybe reset not planed yet.
        break;
    }

    return cube_animation_control(index, tmp, 16, 7);
}

uint8_t clube_layer_rand(cube *data, uint8_t *index)
{
    uint8_t i;

    for(i = 0; i < 8; i++) {
        data->layer_d[15 - *index].row[i] = (uint8_t)rand();
    }
    return 0;
}

uint8_t cube_expand_4(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time)
{
    uint8_t i = 0;
    uint8_t model = 0x80;

    cube_clear(data);

    model = 0x80;
    model >>= *tmp;
    model |= 0x80;

    for(i = (*tmp) - 1; (int8_t)i > 0; i--) {
        data->layer_d[0].row[7 - i] = model;
        data->layer_d[*tmp].row[7 - i] = model;
        data->layer_d[i].row[7] = model;
        data->layer_d[i].row[7 - *tmp] = model;
    }

    model = 0xFF;
    model -= ((1 << (7-*tmp)) - 1);
    
    data->layer_d[*tmp].row[7] = model;
    data->layer_d[*tmp].row[7 - *tmp] = model;
    data->layer_d[0].row[7] = model;
    data->layer_d[0].row[7 - *tmp] = model;

    return cube_animation_control(index, tmp, 15, 7);
}

uint8_t cube_expand_3(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time)
{
    uint8_t i = 0;
    uint8_t model = 0x80;

    cube_clear(data);

    model = 0x01;
    model <<= *tmp;
    model |= 0x01;

    for(i = (*tmp) - 1; (int8_t)i > 0; i--) {
        data->layer_d[0].row[7 - i] = model;
        data->layer_d[*tmp].row[7 - i] = model;
        data->layer_d[i].row[7] = model;
        data->layer_d[i].row[7 - *tmp] = model;
    }

    //model = 0xFF;
    model = ((1 << (*tmp + 1)) - 1);
    
    data->layer_d[*tmp].row[7] = model;
    data->layer_d[*tmp].row[7 - *tmp] = model;
    data->layer_d[0].row[7] = model;
    data->layer_d[0].row[7 - *tmp] = model;

    return cube_animation_control(index, tmp, 15, 7);
}

uint8_t cube_expand_2(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time)
{
    uint8_t i = 0;
    uint8_t model = 0x80;

    cube_clear(data);

    model = 0x01;
    model <<= *tmp;
    model |= 0x01;

    for(i = 1; i < *tmp; i++) {
        data->layer_d[0].row[i] = model;
        data->layer_d[*tmp].row[i] = model;
        data->layer_d[i].row[0] = model;
        data->layer_d[i].row[*tmp] = model;
    }

    //model = 0xFF;
    model = ((1 << (*tmp + 1)) - 1);
    
    data->layer_d[*tmp].row[0] = model;
    data->layer_d[*tmp].row[*tmp] = model;
    data->layer_d[0].row[0] = model;
    data->layer_d[0].row[*tmp] = model;

    return cube_animation_control(index, tmp, 15, 7);
}

uint8_t cube_expand_1(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time)
{
    uint8_t i = 0;
    uint8_t model = 0x80;

    cube_clear(data);

    model = 0x80;
    model >>= *tmp;
    model |= 0x80;

    for(i = 1; i < *tmp; i++) {
        data->layer_d[0].row[i] = model;
        data->layer_d[*tmp].row[i] = model;
        data->layer_d[i].row[0] = model;
        data->layer_d[i].row[*tmp] = model;
    }

    model = 0xFF;
    model -= ((1 << (7-*tmp)) - 1);
    
    data->layer_d[*tmp].row[0] = model;
    data->layer_d[*tmp].row[*tmp] = model;
    data->layer_d[0].row[0] = model;
    data->layer_d[0].row[*tmp] = model;

    return cube_animation_control(index, tmp, 15, 7);
}

void cube_clear(cube *data)
{
	uint8_t i;
	for(i = 0; i < 8; i++) {
		data->layer_f[i] = 0;
	}
}

uint8_t cube_animation_control(uint8_t *index, uint8_t *tmp, uint8_t top, uint8_t chang)
{
    if (*index < chang) {
        (*tmp)++;
    }
    else {
        (*tmp)--;
    }

    if (++*index == top) {
        //if animation is done give one back for a step to the next animation (see readme.txt main folder!!!)
        *index = 0;
        *tmp = 0;
        return 1;
    }

    return 0;
}


uint8_t cube_lift(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time)
{
	//upordown == 1 up , == 0 down
	uint64_t templayer=0;
	uint8_t upordown = 1;
	if(upordown==1) {
		templayer = data->layer_f[0];
		data->layer_f[0] = data->layer_f[1];
		data->layer_f[1] = data->layer_f[2];
		data->layer_f[2] = data->layer_f[3];
		data->layer_f[3] = data->layer_f[4];
		data->layer_f[4] = data->layer_f[5];
		data->layer_f[5] = data->layer_f[6];
		data->layer_f[6] = data->layer_f[7];
		data->layer_f[7] = templayer;
	}
	else {
		templayer = data->layer_f[7];
		data->layer_f[7] = data->layer_f[6];
		data->layer_f[6] = data->layer_f[5];
		data->layer_f[5] = data->layer_f[4];
		data->layer_f[4] = data->layer_f[3];
		data->layer_f[3] = data->layer_f[2];
		data->layer_f[2] = data->layer_f[1];
		data->layer_f[1] = data->layer_f[0];
		data->layer_f[0] = templayer;
	}
	return 1;
}



uint8_t cube_slidesidewards(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time)
{
	//leftorright == 1 left , == 0 right
	uint8_t i = 0, j = 0;
	uint8_t leftorright =1; 
	
	if(leftorright==1) {
		for (i = 0; i <= 7; i++) {
			for (j = 0; j <= 7; j++) {
				
				if (data->layer_d[i].row[j] & 0x01) {
					data->layer_d[i].row[j] = data->layer_d[i].row[j] >> 1;
					data->layer_d[i].row[j] = data->layer_d[i].row[j] | 0x80;
					
				}
				else {
					data->layer_d[i].row[j] = data->layer_d[i].row[j] >> 1;
				}
			}
		}
	}
	
	else {
		for (i = 0; i <= 7; i++) {
			for (j = 0; j <= 7; j++) {
				if (data->layer_d[i].row[j] & 0x80) {
					data->layer_d[i].row[j] = data->layer_d[i].row[j] << 1;
					data->layer_d[i].row[j] = data->layer_d[i].row[j] | 0x01;

				}
				else {
					data->layer_d[i].row[j] = data->layer_d[i].row[j] << 1;
				}
			}
		}
	}
	
	return 1;
}

uint8_t cube_slidebackwards(cube *data, uint8_t *index, uint8_t *tmp, uint8_t *time)
{
	//frontorback == 1 front , == 0 back
	uint8_t i = 0;
	uint8_t temprow=0;
	uint8_t frontorback = 1;
	
	data->layer_d[0].tlc[3] =0x1000; //one
	data->layer_d[1].tlc[3] =0x1800;
	data->layer_d[2].tlc[3] =0x1400;
	data->layer_d[3].tlc[3] =0x1200;
	data->layer_d[4].tlc[3] =0x1000;
	data->layer_d[5].tlc[3] =0x1000;
	data->layer_d[6].tlc[3] =0x1000;
	data->layer_d[7].tlc[3] =0x1000;
	
	if(frontorback==1) {
		for (i = 0; i <= 7; i++) {
			temprow = data->layer_d[i].row[7];
			data->layer_d[i].row[7] = data->layer_d[i].row[6];
			data->layer_d[i].row[6] = data->layer_d[i].row[5];
			data->layer_d[i].row[5] = data->layer_d[i].row[4];
			data->layer_d[i].row[4] = data->layer_d[i].row[3];
			data->layer_d[i].row[3] = data->layer_d[i].row[2];
			data->layer_d[i].row[2] = data->layer_d[i].row[1];
			data->layer_d[i].row[1] = data->layer_d[i].row[0];
			data->layer_d[i].row[0] = temprow;
		}
	}
	else {
		for (i = 0; i <= 7; i++) {
			temprow = data->layer_d[i].row[0];
			data->layer_d[i].row[0] = data->layer_d[i].row[1];
			data->layer_d[i].row[1] = data->layer_d[i].row[2];
			data->layer_d[i].row[2] = data->layer_d[i].row[3];
			data->layer_d[i].row[3] = data->layer_d[i].row[4];
			data->layer_d[i].row[4] = data->layer_d[i].row[5];
			data->layer_d[i].row[5] = data->layer_d[i].row[6];
			data->layer_d[i].row[6] = data->layer_d[i].row[7];
			data->layer_d[i].row[7] = temprow;
		}
	}
	return 1;
}