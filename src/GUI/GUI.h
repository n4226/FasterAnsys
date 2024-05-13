
#include <igl/opengl/glfw/Viewer.h>
#include <unvpp/unvpp.h>
#include <string>
#include <vector>

class GUI
{
public:
    GUI();
    ~GUI();
private:
    /* data */
    std::string

    bool key_down(igl::opengl::glfw::Viewer& viewer, unsigned char key, int modifier);
};

