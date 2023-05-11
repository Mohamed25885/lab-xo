void Delay100ms(unsigned long count)
{
    unsigned long volatile time;
    while (count > 0)
    {
        time = 727240 / 2; // 0.1sec at 80 MHz
        while (time)
        {
            time--;
        }
        count--;
    }
}

void StepRight(int *X, int *Y)
{
    *Y = (++(*X)) >= 3 ? *Y + 1 : *Y;
    *X %= 3;
    *Y %= 3;
}
void StepLeft(int *X, int *Y)
{
    (--(*X));

    *Y = *X < 0 ? *Y - 1 : *Y;
    if (*Y < 0)
        *Y = 2;
    if (*X < 0)
        *X = 2;
}
void StepDown(int *Y)
{
    (*Y) += 1;

    (*Y) %= 3;
}

void StepUp(int *Y)
{
    (*Y) -= 1;

    if (*Y < 0)
        *Y = 2;
}
