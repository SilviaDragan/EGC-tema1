#include "lab_m1/tema1/tema1.h"

#include <vector>
#include <iostream>
#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/lab3/object2D.h"

using namespace std;
using namespace m1;

Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}

void Tema1::Init()
{
    resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    //camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    logicSpace.x = 0;       // logic x
    logicSpace.y = 0;       // logic y
    logicSpace.width = 4;   // logic width
    logicSpace.height = 4;  // logic height

    glm::vec3 corner = glm::vec3(0.001, 0.001, 0);
    length = 0.99f;

    //glm::vec3 corner = glm::vec3(1, 0, 0);
    playerSquareSide = 100, playerSmallPartsSquareSide = 25;
    transPlayerX = 600;
    transPlayerY = 200;
    mouseAngle = 0;

    Mesh* playerBody = object2D::CreateSquare("playerBody", glm::vec3(600, 200, 0), playerSquareSide, glm::vec3(1, 0, 0), true);
    Mesh* playerSmallPart1 = object2D::CreateSquare("playerSmallPart1", glm::vec3(700, 200, 0), playerSmallPartsSquareSide, glm::vec3(0, 1, 0), true);
    Mesh* playerSmallPart2 = object2D::CreateSquare("playerSmallPart2", glm::vec3(700, 200, 0), playerSmallPartsSquareSide, glm::vec3(0, 1, 0), true);

    AddMeshToList(playerBody);
    AddMeshToList(playerSmallPart1);
    AddMeshToList(playerSmallPart2);


}

// Uniform 2D visualization matrix (same scale factor on x and y axes)
glm::mat3 Tema1::VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
    float sx, sy, tx, ty, smin;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    if (sx < sy)
        smin = sx;
    else
        smin = sy;
    tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
    ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

    return glm::transpose(glm::mat3(
        smin, 0.0f, tx,
        0.0f, smin, ty,
        0.0f, 0.0f, 1.0f));
}

void Tema1::SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor, bool clear)
{
    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
    GetSceneCamera()->Update();
}

void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // asta era inainte de viewport si chestii

    //glm::ivec2 resolution = window->GetResolution();
    //// Sets the screen area where to draw
    //glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds) 
{
    playerModelMatrix = glm::mat3(1);
    playerModelMatrix =
        transform2D::Translate(transPlayerX, transPlayerY) *
        /*transform2D::Rotate(mouseAngle) **/
        transform2D::Translate(-transPlayerX - (playerSquareSide / 2), -transPlayerY - (playerSquareSide / 2));
    RenderMesh2D(meshes["playerBody"], shaders["VertexColor"], playerModelMatrix);

    playerModelMatrix = glm::mat3(1);
    playerModelMatrix *= transform2D::Translate(transPlayerX + playerSquareSide, transPlayerY);
    RenderMesh2D(meshes["playerSmallPart1"], shaders["VertexColor"], playerModelMatrix);
   
    playerModelMatrix = glm::mat3(1);
    playerModelMatrix *= transform2D::Translate(transPlayerX + playerSquareSide, transPlayerY + (playerSquareSide- playerSmallPartsSquareSide));
    RenderMesh2D(meshes["playerSmallPart2"], shaders["VertexColor"], playerModelMatrix);



}

void Tema1::FrameEnd()
{
}


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    mouseAngle = atan2(mouseX - resolution.x/2 - playerSquareSide / 2, mouseY - resolution.y/2 - playerSquareSide / 2);

}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}