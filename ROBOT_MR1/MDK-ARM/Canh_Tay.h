#define MINIMUM_ENCODER_CANH_TAY_DISTANCE 20

#define MIN_MOTOR_CANH_TAY_SPEED 0
#define NEURAL_MOTOR_CANH_TAY_SPEED 2
#define MAX_MOTOR_CANH_TAY_SPEED 250

// Y = 44cm
// X1 = 61cm
// X2 = 25cm
// X = 86cm

// Encoder canh tay X
// 1 vong 360 do = 2500 xung
// canh tay bi nguoc
int Encoder_Canh_Tay_X = 0;
int Min_Encoder_Canh_Tay_X = -7000;
int Max_Encoder_Canh_Tay_X = 0;
int Target_Encoder_Canh_Tay_X = 0;
int Encoder_Canh_Tay_X_Resolution = 1;

// Milimet canh tay X
int Milimet_Canh_Tay_X = 0; // milimet
int Min_Milimet_Canh_Tay_X = 0;
int Max_Milimet_Canh_Tay_X = 610;
int Target_Milimet_Canh_Tay_X = 0;

// Encoder canh tay Y
// 1 vong 360 do = 2500 xung
int Encoder_Canh_Tay_Y = 0;
int Min_Encoder_Canh_Tay_Y = 0;
int Max_Encoder_Canh_Tay_Y = 4500;
int Target_Encoder_Canh_Tay_Y = 0;
int Encoder_Canh_Tay_Y_Resolution = 1;

// Milimet canh tay Y
int Milimet_Canh_Tay_Y = 0; // milimet
int Min_Milimet_Canh_Tay_Y = 0;
int Max_Milimet_Canh_Tay_Y = 440; // 44cm
int Target_Milimet_Canh_Tay_Y = 0;

// Trang Thai X
// 0: giu im
// 1: ra
// 2: vao
int Trang_Thai_Canh_Tay_X = 0;

// Trang Thai Y
// 0: giu im
// 1: len
// 2: xuong
int Trang_Thai_Canh_Tay_Y = 0;

// Reset
bool reset_Canh_Tay_X = true;
int reset_Canh_Tay_Y = true;

void reset_Encoder_Canh_Tay_X()
{
    TIM3->CNT = 0;
    num_over_t3 = 0;
}

void reset_Encoder_Canh_Tay_Y()
{
    TIM5->CNT = 0;
    num_over_t5 = 0;
}

int get_Encoder_Canh_Tay_X()
{
    Encoder_Canh_Tay_X = Chong_Nhieu_ADC(ENCODER_CANH_TAY_X);
    return Encoder_Canh_Tay_X;
}

int get_Encoder_Canh_Tay_Y()
{
    Encoder_Canh_Tay_Y = Chong_Nhieu_ADC(ENCODER_CANH_TAY_Y);
    return Encoder_Canh_Tay_Y;
}

void move_Canh_Tay_X()
{
    get_Encoder_Canh_Tay_X();
    Milimet_Canh_Tay_X = mapRange_int(Encoder_Canh_Tay_X, Min_Encoder_Canh_Tay_X, Max_Encoder_Canh_Tay_X, Min_Milimet_Canh_Tay_X, Max_Milimet_Canh_Tay_X);

    // Target_Encoder_Canh_Tay_X = mapRange_int(Target_Milimet_Canh_Tay_X, Min_Milimet_Canh_Tay_X, Max_Milimet_Canh_Tay_X, Min_Encoder_Canh_Tay_X, Max_Encoder_Canh_Tay_X);

    if (abs(Target_Encoder_Canh_Tay_X - Encoder_Canh_Tay_X) < MINIMUM_ENCODER_CANH_TAY_DISTANCE)
    {
        Trang_Thai_Canh_Tay_X = 0;
    }
    else
    {
        if (Target_Encoder_Canh_Tay_X < Encoder_Canh_Tay_X)
        {
            Trang_Thai_Canh_Tay_X = 2; // vao
        }
        else
        {
            Trang_Thai_Canh_Tay_X = 1; // ra
        }
    }

    // check cam bien tu
    if (Trang_Thai_Canh_Tay_X == 2 && CAM_BIEN_TU_X_VAO) // neu vao + cam bien tu -> dung
    {
        Trang_Thai_Canh_Tay_X = 0;
    }
    // check range canh tay
    if (Encoder_Canh_Tay_X > Max_Encoder_Canh_Tay_X || Encoder_Canh_Tay_X < Min_Encoder_Canh_Tay_X)
    {
        Trang_Thai_Canh_Tay_X = 0;
    }

    switch (Trang_Thai_Canh_Tay_X)
    {
    case 0:
        MOTOR_CANH_TAY_X = NEURAL_MOTOR_CANH_TAY_SPEED;
        break;

    case 1:
        MOTOR_CANH_TAY_X = MAX_MOTOR_CANH_TAY_SPEED;
        MOTOR_CANH_TAY_X_RA;
        break;

    case 2:
        MOTOR_CANH_TAY_X = MAX_MOTOR_CANH_TAY_SPEED;
        MOTOR_CANH_TAY_X_VAO;
        break;
    };
}

void move_Canh_Tay_Y()
{
    Encoder_Canh_Tay_Y = get_Encoder_Canh_Tay_Y();
    Milimet_Canh_Tay_Y = mapRange_int(Encoder_Canh_Tay_Y, Min_Encoder_Canh_Tay_Y, Max_Encoder_Canh_Tay_Y, Min_Milimet_Canh_Tay_Y, Max_Milimet_Canh_Tay_Y);

    // Target_Encoder_Canh_Tay_Y = mapRange_int(Target_Milimet_Canh_Tay_Y, Min_Milimet_Canh_Tay_Y, Max_Milimet_Canh_Tay_Y, Min_Encoder_Canh_Tay_Y, Max_Encoder_Canh_Tay_Y);

    if (abs(Target_Encoder_Canh_Tay_Y - Encoder_Canh_Tay_Y) < MINIMUM_ENCODER_CANH_TAY_DISTANCE)
    {
        Trang_Thai_Canh_Tay_Y = 0;
    }
    else
    {
        if (Target_Encoder_Canh_Tay_Y < Encoder_Canh_Tay_Y)
        {
            Trang_Thai_Canh_Tay_Y = 2; // xuong
        }
        else
        {
            Trang_Thai_Canh_Tay_Y = 1; // len
        }
    }

    if (Trang_Thai_Canh_Tay_Y == 2 && CAM_BIEN_TU_Y_DUOI) // neu xuong + cam bien tu duoi -> dung
    {
        Trang_Thai_Canh_Tay_Y = 0;
    }

    if (Trang_Thai_Canh_Tay_Y == 1 && CAM_BIEN_TU_Y_TREN)
    {
        Trang_Thai_Canh_Tay_X = 0;
    }

    // check range canh tay
    if (Encoder_Canh_Tay_Y > Max_Encoder_Canh_Tay_Y || Encoder_Canh_Tay_Y < Min_Encoder_Canh_Tay_Y)
    {
        Trang_Thai_Canh_Tay_Y = 0;
    }

    switch (Trang_Thai_Canh_Tay_Y)
    {
    case 0:
        MOTOR_CANH_TAY_Y = NEURAL_MOTOR_CANH_TAY_SPEED;
        break;

    case 1:
        MOTOR_CANH_TAY_Y = MAX_MOTOR_CANH_TAY_SPEED;
        MOTOR_CANH_TAY_Y_LEN;
        break;

    case 2:
        MOTOR_CANH_TAY_Y = MAX_MOTOR_CANH_TAY_SPEED;
        MOTOR_CANH_TAY_Y_XUONG;
        break;
    }
}

void set_Target_Canh_Tay_X_milimets(int milimets)
{
    Target_Milimet_Canh_Tay_X = milimets;
    Target_Milimet_Canh_Tay_X = map_Min_Max(Target_Milimet_Canh_Tay_X, Min_Milimet_Canh_Tay_X, Max_Milimet_Canh_Tay_X);
    Target_Encoder_Canh_Tay_X = mapRange_int(Target_Milimet_Canh_Tay_X, Min_Milimet_Canh_Tay_X, Max_Milimet_Canh_Tay_X, Min_Encoder_Canh_Tay_X, Max_Encoder_Canh_Tay_X);
}

void set_Target_Canh_Tay_X_encoders(int encoders)
{
    Target_Encoder_Canh_Tay_X = encoders;
    Target_Encoder_Canh_Tay_X = map_Min_Max(Target_Encoder_Canh_Tay_X, Min_Encoder_Canh_Tay_X, Max_Encoder_Canh_Tay_X);
    Target_Milimet_Canh_Tay_X = mapRange_int(Target_Encoder_Canh_Tay_X, Min_Encoder_Canh_Tay_X, Max_Encoder_Canh_Tay_X, Min_Milimet_Canh_Tay_X, Max_Milimet_Canh_Tay_X);
}

void set_Target_Canh_Tay_Y_milimets(int milimets)
{
    Target_Milimet_Canh_Tay_Y = milimets;
    Target_Milimet_Canh_Tay_Y = map_Min_Max(Target_Milimet_Canh_Tay_Y, Min_Milimet_Canh_Tay_Y, Max_Milimet_Canh_Tay_Y);
    Target_Encoder_Canh_Tay_Y = mapRange_int(Target_Milimet_Canh_Tay_Y, Min_Milimet_Canh_Tay_Y, Max_Milimet_Canh_Tay_Y, Min_Encoder_Canh_Tay_Y, Max_Encoder_Canh_Tay_Y);
}

void set_Target_Canh_Tay_Y_encoders(int encoders)
{
    Target_Encoder_Canh_Tay_Y = encoders;
    Target_Encoder_Canh_Tay_Y = map_Min_Max(Target_Encoder_Canh_Tay_Y, Min_Encoder_Canh_Tay_Y, Max_Encoder_Canh_Tay_Y);
    Target_Milimet_Canh_Tay_Y = mapRange_int(Target_Encoder_Canh_Tay_Y, Min_Encoder_Canh_Tay_Y, Max_Encoder_Canh_Tay_Y, Min_Milimet_Canh_Tay_Y, Max_Milimet_Canh_Tay_Y);
}

int get_Trang_Thai_Canh_Tay_X()
{
    return Trang_Thai_Canh_Tay_X;
}

int get_Trang_Thai_Canh_Tay_Y()
{
    return Trang_Thai_Canh_Tay_Y;
}

void task_Reset_Canh_Tay_X()
{
    while (CAM_BIEN_TU_X_VAO)
    {
        MOTOR_CANH_TAY_X = MAX_MOTOR_CANH_TAY_SPEED;
        MOTOR_CANH_TAY_X_VAO;
        vTaskDelay(5);
    }
    MOTOR_CANH_TAY_X = NEURAL_MOTOR_BAN_TAY_SPEED;
    reset_Encoder_Canh_Tay_X();
    vTaskDelay(5);

    while (get_Encoder_Canh_Tay_X() < Min_Encoder_Canh_Tay_X)
    {
        MOTOR_CANH_TAY_X = MAX_MOTOR_CANH_TAY_SPEED;
        MOTOR_CANH_TAY_X_RA;
        vTaskDelay(5);
    }
    MOTOR_CANH_TAY_X = NEURAL_MOTOR_BAN_TAY_SPEED;
}

void task_Reset_Canh_Tay_Y()
{

    while (CAM_BIEN_TU_Y_DUOI)
    {
        MOTOR_CANH_TAY_Y = MAX_MOTOR_CANH_TAY_SPEED;
        MOTOR_CANH_TAY_Y_XUONG;
        vTaskDelay(5);
    }
    MOTOR_CANH_TAY_Y = NEURAL_MOTOR_CANH_TAY_SPEED;
    vTaskDelay(5);

    while (CAM_BIEN_TU_Y_TREN)
    {
        MOTOR_CANH_TAY_Y = MAX_MOTOR_CANH_TAY_SPEED;
        MOTOR_CANH_TAY_Y_LEN;
        vTaskDelay(5);
    }
    MOTOR_CANH_TAY_Y = NEURAL_MOTOR_CANH_TAY_SPEED;
    vTaskDelay(5);

    while (CAM_BIEN_TU_Y_DUOI)
    {
        MOTOR_CANH_TAY_Y = MAX_MOTOR_CANH_TAY_SPEED;
        MOTOR_CANH_TAY_Y_XUONG;
        vTaskDelay(5);
    }

    MOTOR_CANH_TAY_Y = NEURAL_MOTOR_CANH_TAY_SPEED;
    vTaskDelay(5);
    reset_Encoder_Canh_Tay_Y();
}