void trim_space(char* src)
{
    int i , j ;
    for(i = -1, j = 0; j < strlen(src); j ++ )
    {
        if(!is_space(src[j]))
        { 
            if(src[j] >= 'A' && src[j] <= 'Z')
            {
                src[++i] = src[j] + 32 ;
            }else
            {
                src[++i] = src[j];
            }
        }else
        {
            if(i != -1 && !is_space(src[i]) )
            {
                src[++i] = ' ' ;
            }
        }
    }
    for(;i>=0 ; i--)
    {
        if(!is_space(src[i]))
        {
            break ;
        }
    }
    src[++i] = '\0' ;
}