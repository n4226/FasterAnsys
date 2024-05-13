
#include <igl/opengl/glfw/Viewer.h>
#include <unvpp/unvpp.h>
#include <string>
#include <vector>

class GUI
{
public:
    GUI(const std::string& cadFIle);
    ~GUI();

    void start();

private:
    /* data */
    std::string cadFile;

    unvpp::Mesh mesh;


    bool key_down(igl::opengl::glfw::Viewer& viewer, unsigned char key, int modifier);
};

