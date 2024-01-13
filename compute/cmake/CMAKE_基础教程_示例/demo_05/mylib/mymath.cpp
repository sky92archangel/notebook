


double power(double base , double exp)
{
    int res = base;
    if(base ==1)
    {
        return 1;
    }
    for (int i = 1; i < exp; i++)
    {
        res = res*base;
    }
    return res;
}