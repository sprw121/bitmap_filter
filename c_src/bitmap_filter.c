#include <erl_nif.h>

/*
    This function expects a list of list of tuples of type {int, _}.
    It filters the tuples, using the first int field as a key,
    and removing duplicating keys with precedence given the the order
    in which they were seen (first given precedence).
*/
static ERL_NIF_TERM
bitmap_filter(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    size_t seen_forklift_id[3000] = { 0 };

    if(argc != 1)
    {
        return enif_make_badarg(env);
    }

    if(!enif_is_list(env, argv[0]))
    {
        return enif_make_badarg(env);
    }

    ERL_NIF_TERM ret = enif_make_list(env, 0);

    ERL_NIF_TERM outer_list = argv[0];
    ERL_NIF_TERM inner_list;

    ERL_NIF_TERM inner_head;

    const ERL_NIF_TERM* tuple_elems;
    int num_elems;
    unsigned int key;

    while(enif_get_list_cell(env, outer_list, &inner_list, &outer_list))
    {
        if(!enif_is_list(env, inner_list))
        {
            return enif_make_badarg(env);
        }

        while(enif_get_list_cell(env, inner_list, &inner_head, &inner_list))
        {
            if(!enif_get_tuple(env, inner_head, &num_elems, &tuple_elems))
            {
                return enif_make_badarg(env);
            }

            if(num_elems != 2)
            {
                return enif_make_badarg(env);
            }

            if(!enif_get_uint(env, tuple_elems[0], &key))
            {
                return enif_make_badarg(env);
            }

            if(key >= 3000)
            {
                return enif_make_badarg(env);
            }

            if(!seen_forklift_id[key])
            {
                seen_forklift_id[key] = 1;
                ret = enif_make_list_cell(env, inner_head, ret);
            }
        }
    }

    return ret;
}

static ErlNifFunc nif_funcs[] =
{
    {"filter", 1, bitmap_filter, 0}
};

ERL_NIF_INIT(bitmap_filter, nif_funcs, NULL, NULL, NULL, NULL)
