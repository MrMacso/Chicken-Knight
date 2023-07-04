#include "HowToPlayState.h"

bool HowToPlayState::OnEnter()
{
    m_howToBackground.Load("assets/images/MenuKnight.png");
    m_howToBackground.SetImageDimension(1, 1, 960, 533);
    m_howToBackground.SetSpriteDimension(1920, 1121);

    auto loadButton = [](Button& name, const std::string& loadOriginal, const std::string& loadSelect,
        float heightPos, float widthPos)
    {
        name.CreateButton(loadOriginal, loadSelect, 300, 120);
        name.SetButtonDimension(300, 120);
        name.SetButtonPosition(heightPos, widthPos);
    };
    loadButton(m_exitButton, "assets/images/BackB.png", "assets/images/BackBSelect.png", 1580, 950);

    m_text.Initialize();
    m_text.Load("assets/images/fontbold.ttf", 150);
    m_text.SetText("Stay alive as long as possible!");
    m_text.SetDimension(900, 160);

    m_textTwo.Initialize();
    m_textTwo.Load("assets/images/fontbold.ttf", 150);
    m_textTwo.SetText("Move:WASD , Slide:Tab, Heal:Q(cheat)");
    m_textTwo.SetDimension(900, 160);

    return true;
}

GameState* HowToPlayState::Update()
{
    SDL_Point mousePos = Input::Instance()->GetMousePosition();
    bool isMouseClicked = Input::Instance()->IsMouseClicked();
    SDL_Rect exitCollider = m_exitButton.GetCollider();

    if (SDL_PointInRect(&mousePos, &exitCollider) && isMouseClicked == true)
    {
        return new MenuState;
    }
    return this;
}

bool HowToPlayState::Render()
{
    m_howToBackground.Render(0, 0, 0);
    m_text.Render(500, 400);
    m_textTwo.Render(500, 600);
    m_exitButton.Render();
    return true;
}

void HowToPlayState::OnExit()
{
    m_howToBackground.Unload();
}
