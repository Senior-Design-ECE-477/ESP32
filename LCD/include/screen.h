#ifndef SCREEN_CONTROLLER_H
#define SCREEN_CONTROLLER_H

#ifdef __cplusplus
extern "C"
{
#endif /* C++ */


class ScreenController
{
public:
    ScreenController();
    void accepted(int ms);
    void denied(int ms);
    void home();

private:
    static const int something = 1;
};

#ifdef __cplusplus
}
#endif /* C++ */

#endif /* SCREEN_CONTROLLER_H */