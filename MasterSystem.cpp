#include "Config.h"
#include "MasterSystem.h"
#include "Emulator.h"

static const int WIDTH_RESOLUTION = 256;
static const int HEIGHT_RESOLUTION = 192;
static const int SCREEN_SCALE = 1;

MasterSystem* MasterSystem::m_Instance = 0;

MasterSystem* MasterSystem::CreateInstance() {
	if (0 == m_Instance)
		m_Instance = new MasterSystem();
	return m_Instance;
}

MasterSystem::MasterSystem(void) :
	m_Emulator(NULL),
	m_UseGFXOpt(false) {
	m_Emulator = Emulator::CreateInstance();
}

MasterSystem::~MasterSystem(void) {
	delete m_Emulator;
}

bool MasterSystem::CreateSDLWindow() {
	m_Width = WIDTH_RESOLUTION * SCREEN_SCALE;
	m_Height = HEIGHT_RESOLUTION * SCREEN_SCALE;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return false;
	if (SDL_SetVideoMode(m_Width, m_Height, 8, SDL_OPENGL) == NULL)
		return false;

	InitGL();

	SDL_WM_SetCaption("SMS", NULL);

	return true;
}

void MasterSystem::InitGL() {
	glViewport(0, 0, m_Width, m_Height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(0, m_Width, m_Height, 0, -1.0, 1.0);
	glClearColor(0, 0, 0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_FLAT);

	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DITHER);
	glDisable(GL_BLEND);
}

void MasterSystem::StartRom(const char* path) {

}

void MasterSystem::BeginGame(int fps, bool useGFXOpt) {

}

void MasterSystem::RomLoop(int fps) {

}

void MasterSystem::RenderGame() {

}

unsigned char MasterSystem::GetMemoryByte(int i) {

}

void MasterSystem::HandleInput(const SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		printf("Key down");
	}
}