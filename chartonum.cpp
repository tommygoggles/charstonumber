#include <cstdio>
#include <cstdlib>
#include <assert.h>


typedef float tgnumber;


enum numsearchstate
{
	looking,
	numbernext,
	innumber,
	afterdecimal
};




template<class tgnumber>

#define floatyatoitg

tgnumber atoitg (const char* textin)
{
	numsearchstate searchstate = looking;
	tgnumber retval = 0;
	bool negit = false;

	#ifdef floatyatoitg
	long long afterbit = 0;
	long long multiply = 1;
	#endif

	unsigned int current = 0;
    bool done = false;
	for(;!done;current++)
	{
        switch (textin[current])
        {
            default:
            switch (searchstate)
            {
                case (looking):

                break;
                default:
                done = true;
                break;
            }
            break;

            case (0):
                done = true;
            break;

            case ('.'):
            switch (searchstate)
             {
                #ifdef floatyatoitg
                case (looking):
                case (innumber):
                //change after decimal
                searchstate = afterdecimal;
                break;
                #endif

                default:
                    done = true;
                break;
             }
            break;

            case ('-'):
             switch (searchstate)
             {
                case (looking):
                //make it minus
                negit = true;
                searchstate = numbernext;
                break;
                default:
                    done = true;
                break;
             }
            break;

            case ('0'):
            case ('1'):
            case ('2'):
            case ('3'):
            case ('4'):
            case ('5'):
            case ('6'):
            case ('7'):
            case ('8'):
            case ('9'):
            tgnumber thisval = textin[current] - 48;
            switch (searchstate)
            {
                case (looking):
                case (numbernext):
                searchstate = innumber;
                case (innumber):
                retval *=10;
                retval += thisval;
                break;

                case (afterdecimal):
                #ifdef floatyatoitg
                multiply *= 10;
                afterbit *= 10;
                afterbit += thisval;
                #endif
                break;
             }
            break;
        }
	}

	if(!negit)
    {
        #ifdef floatyatoitg
        return retval+( (tgnumber)afterbit/ (tgnumber)multiply);
        #else
        return retval;
        #endif
    }
    else
    {
        #ifdef floatyatoitg
        return 0 - (retval+( (tgnumber)afterbit/ (tgnumber)multiply));
        #else
        return 0 - retval;
        #endif
    }
	//return 0;
}



int main ()
{
    unsigned int floatnumber = 0;//119182262
    unsigned int right = 0;
    float& asafloat = *(reinterpret_cast<float*> (&floatnumber));
    asafloat = 100.0f;
    char buffer[128];
    int ret;
    float g;

    do
    {
        ret = snprintf(buffer, sizeof buffer, "%.*f",60, asafloat);
        if (ret < 0)
        {
            assert(false);
        }
        else
        {
            if(ret > sizeof buffer)
            {
                assert(false);
            }
        }
        g = atoitg<float>(buffer);
        //g = atof(buffer);
        if(asafloat == g)
        {
            right++;
        }
        floatnumber++;
    }
    while (floatnumber);
    printf("%d",right);
}
