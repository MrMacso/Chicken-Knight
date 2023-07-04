#include "MenuState.h"

bool MenuState::OnEnter()
{
    m_background.Load("assets/images/MenuBG.png");
    m_background.SetImageDimension(1, 1, 728, 410);
    m_background.SetSpriteDimension(1920, 1121);


    auto loadButton = [](Button& name, const std::string& loadOriginal, const std::string& loadSelect,
        float heightPos, float widthPos)
    {
        name.CreateButton(loadOriginal, loadSelect, 300, 120);
        name.SetButtonDimension(300, 120);
        name.SetButtonPosition(heightPos, widthPos);
    };
    loadButton(m_startButton, "assets/images/StartB.png", "assets/images/StartBSelect.png", 810, 400);
    loadButton(m_howToButton, "assets/images/HowToB.png", "assets/images/HowToBSelect.png", 810, 550);
    loadButton(m_exitButton, "assets/images/ExitB.png", "assets/images/ExitBSelect.png", 810, 700);

    m_text.Initialize();
    m_text.Load("assets/text/fontbold.ttf", 50);
    m_text.SetColor(255, 0, 0, static_cast<Uint8>(0.8));
    m_text.SetDimension(400, 155);
    return true;
}
//======================================================================
GameState* MenuState::Update()
{
    SDL_Point mousePos = Input::Instance()->GetMousePosition();
    bool isMouseClicked = Input::Instance()->IsMouseClicked();

    SDL_Rect startCollider = m_startButton.GetCollider();
    SDL_Rect howToCollider = m_howToButton.GetCollider();
    SDL_Rect exitCollider = m_exitButton.GetCollider();

    m_text.SetText("CHICKEN KNIGHT");

    if (SDL_PointInRect(&mousePos, &startCollider) && isMouseClicked == true)
    {
        return new PlayState;
    }
    if (SDL_PointInRect(&mousePos, &howToCollider) && isMouseClicked == true)
    {
        return new HowToPlayState;
    }
    if (SDL_PointInRect(&mousePos, &exitCollider) && isMouseClicked == true)
    {
        return nullptr;
    }
    return this;
}
//======================================================================
bool MenuState::Render()
{
    m_background.Render(0, 0, 0);
    m_startButton.Render();
    m_howToButton.Render();
    m_exitButton.Render();
    m_text.Render(750, 40);

    return true;
}
//======================================================================
void MenuState::OnExit()
{
    m_background.Unload();
}