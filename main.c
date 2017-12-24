#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "hashmap.h"

#define KEY_COUNT		(1024 * 1024)
#define	KEY_PREFIX		("test")
#define	KEY_MAX_LENGTH	(256)

typedef struct	s_data
{
	char	key_string[KEY_MAX_LENGTH];
	int		number;
}				t_data;

int	main(void)
{
	t_hashmap_env	env;
	t_hashmap		*map;
	int				index;
	char			key_string[KEY_MAX_LENGTH];
	t_data			*value;
	int				error;
	
	hashmap_init(&env);
	map = hashmap_new();
	if (map == NULL)
		exit(1);
	index = 0;
	while (index < KEY_COUNT)
	{
		value = (t_data*)malloc(sizeof(t_data));
		snprintf(value->key_string, KEY_MAX_LENGTH, "%s%d", KEY_PREFIX, index);
		value->number = index;
		error = hashmap_put(&env, map, value->key_string, value);
		assert(error == MAP_OK);
		index++;
	}
	index = 0;
	while (index < KEY_COUNT)
	{
		snprintf(key_string, KEY_MAX_LENGTH, "%s%d", KEY_PREFIX, index);
		error = hashmap_get(&env, map, key_string, (void**)&value);
		assert(error == MAP_OK);
		assert(value->number == index);
		index++;
	}
	snprintf(key_string, KEY_MAX_LENGTH, "%s%d", KEY_PREFIX, KEY_COUNT);
	error = hashmap_get(&env, map, key_string, (void**)&value);
	assert(error == MAP_MISSING);
	index = 0;
	while (index < KEY_COUNT)
	{
		snprintf(key_string, KEY_MAX_LENGTH, "%s%d", KEY_PREFIX, index);
		error = hashmap_get(&env, map, key_string, (void**)&value);
		assert(error == MAP_OK);
		error = hashmap_remove(&env, map, key_string);
		assert(error == MAP_OK);
		free(value);
		index++;
	}
	hashmap_free(map);
	return (0);
}
