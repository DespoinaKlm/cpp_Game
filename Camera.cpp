#include "Camera.h"

//---------------------Constructor-------------------------
Camera::Camera()
{
    m_x_start = 0.0f;
    m_y_start = 0.0f;
    m_width = CANVAS_WIDTH;
    m_height = CANVAS_HEIGHT;
}

//---------------------Destructor--------------------------
Camera::~Camera()
{
}

void Camera::Update(float dt)
{
    if (m_unique_camera != nullptr) {
        m_x_start = m_player_target->Point_X - CANVAS_WIDTH / 2;
        m_y_start = m_player_target->Point_Y - CANVAS_HEIGHT / 2;

        if (m_x_start < 0) {
            m_x_start = 0;
        }
        if (m_y_start < 0) {
            m_y_start = 0;
        }
        if (m_x_start >( 2 * CANVAS_WIDTH - m_width)) {
            m_x_start = 2 * CANVAS_WIDTH - m_width;
        }
        if (m_y_start > (2 * CANVAS_HEIGHT - m_height)) {
            m_y_start = 2 * CANVAS_HEIGHT - m_height;
        }

        position = Vector2D(m_x_start, m_y_start);
    }
}

Vector2D Camera::GetPosition()
{
    return position;
}

void Camera::SetPoint(Point* target)
{
    m_player_target = target;
}

//---------------------GetCamera---------------------------
Camera* Camera::GetCamera()
{
    if (m_unique_camera == nullptr) {
        m_unique_camera = new Camera();
    }
    return m_unique_camera;
}

Camera* Camera::m_unique_camera = nullptr;  