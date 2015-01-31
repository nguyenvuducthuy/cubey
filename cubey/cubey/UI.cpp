#include "UI.h"

#include "GLFW/glfw3.h"
#include "Input.h"
#include "Camera.h"

namespace cubey {

	void UI::SystemInit() {
		TwInit(TW_OPENGL, NULL);
		EventChannel<Engine::WindowSizeEvent>::DirtyAdd([](const Engine::WindowSizeEvent& e){
			TwWindowSize(e.width, e.height); 
		});
		EventChannel<Engine::MouseButtonEvent>::DirtyAdd([](const Engine::MouseButtonEvent& e){
			Input::Main()->mouse_button_consumed_by_ui_ = TwEventMouseButtonGLFW(e.button, e.action);
		});
		EventChannel<Engine::MousePosEvent>::DirtyAdd([](const Engine::MousePosEvent& e){
			TwEventMousePosGLFW(e.xpos, e.ypos); 
		});
		EventChannel<Engine::MouseWheelEvent>::DirtyAdd([](const Engine::MouseWheelEvent& e){
			Input::Main()->mouse_wheel_consumed_by_ui_ = TwEventMouseWheelGLFW(e.yoffset);
		});
		EventChannel<Engine::KeyEvent>::DirtyAdd([](const Engine::KeyEvent& e){
			TwEventKeyGLFW(e.key, e.action); 
		});
		EventChannel<Engine::CharEvent>::DirtyAdd([](const Engine::CharEvent& e){
			TwEventCharGLFW(e.codepoint, GLFW_PRESS); 
		});

		tw_bar_ = TwNewBar("cubey!");
		int w, h;
		glfwGetWindowSize(Engine::window_, &w, &h);
		TwWindowSize(w, h);
		TwDefine(" GLOBAL help='AntTweakBar Test' ");
		TwDefine("cubey! size = '320 640'");

		TwAddVarRO(tw_bar_, "time", TW_TYPE_DOUBLE, &Time::time_since_start_, "precision=2 help='Time Since Start.' ");
		TwAddVarRO(tw_bar_, "frame time", TW_TYPE_DOUBLE, &Time::frame_time_, "precision=4 help='Frame Time.' ");
		TwAddVarRO(tw_bar_, "fps", TW_TYPE_DOUBLE, &Time::raw_fps_, "precision=2 help='Frame Per Second' ");
		
		TwAddVarRO(tw_bar_, "delta time", TW_TYPE_DOUBLE, &Time::delta_time_, "precision=4 help='Delta Time.' ");
		TwAddVarRO(tw_bar_, "regulated fps", TW_TYPE_DOUBLE, &Time::regulated_fps_, "precision=2 help='Regulated FPS.' ");

		TwAddVarRO(tw_bar_, "camera position", TW_TYPE_DIR3F, &Camera::Main()->transform_.position_, "");
		TwAddVarRO(tw_bar_, "camera orientation", TW_TYPE_QUAT4F, &Camera::Main()->transform_.orientation_, "");
		//TwAddVarRO(bar, "camera euler angles", TW_TYPE_DIR3F, &Camera::Main()->transform_.euler_angles_, "");

		//TwAddVarRO(bar, "camera forward", TW_TYPE_DIR3F, &Camera::Main()->transform_.forward_, "");
		//TwAddVarRO(bar, "camera right", TW_TYPE_DIR3F, &Camera::Main()->transform_.right_, "");
		//TwAddVarRO(bar, "camera up", TW_TYPE_DIR3F, &Camera::Main()->transform_.up_, "");

		//TwAddVarRO(bar, "camera target", TW_TYPE_DIR3F, &Camera::Main()->look_at_target_pos_, "");
		//TwAddVarRO(bar, "camera yaw", TW_TYPE_FLOAT, &Camera::Main()->yaw_, "");
		//TwAddVarRO(bar, "camera pitch", TW_TYPE_FLOAT, &Camera::Main()->pitch_, "");
		//TwAddVarRO(bar, "camera roll", TW_TYPE_FLOAT, &Camera::Main()->roll_, "");
	}

	void UI::UIRender() {
		TwDraw();
	}

	void UI::Terminate() {
		TwTerminate();
	}

}