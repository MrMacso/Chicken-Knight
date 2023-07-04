#include "GameOverState.h"

bool GameOverState::OnEnter()
{
    m_exitBackground.Load("assets/images/MenuKnight.png");
    m_exitBackground.SetImageDimension(1, 1, 960, 533);
    m_exitBackground.SetSpriteDimension(1920, 1121);

    m_gameOvertext.Initialize();
    m_gameOvertext.Load("assets/text/fontbold.ttf", 120);
    m_gameOvertext.SetColor(56, 255, 0, static_cast<Uint8>(0.8f));
    m_gameOvertext.SetDimension(400, 150);
    m_gameOvertext.SetText("GAME OVER");

    auto loadButton = [](Button& name, const std::string& loadOriginal, const std::string& loadSelect,
        float heightPos, float widthPos)
    {
        name.CreateButton(loadOriginal, loadSelect, 300, 120);
        name.SetButtonDimension(300, 120);
        name.SetButtonPosition(heightPos, widthPos);
    };
    loadButton(m_restartButton, "assets/images/BackB.png", "assets/images/BackBSelect.png", 625, 600);
    loadButton(m_exitButton, "assets/images/ExitB.png", "assets/images/ExitBSelect.png", 1175, 600);

    return true;
}

GameState* GameOverState::Update()
{
    SDL_Point mousePos = Input::Instance()->GetMousePosition();
    bool isMouseClicked = Input::Instance()->IsMouseClicked();
    SDL_Rect restartCollider = m_restartButton.GetCollider();
    SDL_Rect exitCollider = m_exitButton.GetCollider();



    if (SDL_PointInRect(&mousePos, &restartCollider) && isMouseClicked == true)
    {
        return new MenuState;
    }
    if (SDL_PointInRect(&mousePos, &exitCollider) && isMouseClicked == true)
    {
        return nullptr;
    }
    return this;
}

bool GameOverState::Render()
{
    m_exitBackground.Render(0, 0, 0);
    m_gameOvertext.Render(750, 300);
    m_restartButton.Render();
    m_exitButton.Render();
    return true;
}

void GameOverState::OnExit()
{
    m_exitBackground.Unload();
}
