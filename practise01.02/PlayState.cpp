#include "PlayState.h"
#include "MenuState.h"


bool PlayState::OnEnter()
{
    m_inGame.OnEnter();


    auto loadButton = [](Button& name, const std::string& loadOriginal, const std::string& loadSelect,
        float heightPos, float widthPos)
    {
        name.CreateButton(loadOriginal, loadSelect, 300, 120);
        name.SetButtonDimension(150, 60);
        name.SetButtonPosition(heightPos, widthPos);
    };
    loadButton(m_exitButton, "assets/images/BackB.png", "assets/images/BackBSelect.png", 1760, 20);

    return true;
}

GameState* PlayState::Update()
{
    SDL_Point mousePos = Input::Instance()->GetMousePosition();
    bool isMouseClicked = Input::Instance()->IsMouseClicked();
    SDL_Rect exitCollider = m_exitButton.GetCollider();

    m_inGame.Update();

    if (SDL_PointInRect(&mousePos, &exitCollider) && isMouseClicked == true)
    {
        return new MenuState;
    }
    if (m_inGame.GetIsDead() == true)
    {
        return new  GameOverState;
    }
    return this;
}

bool PlayState::Render()
{
    m_inGame.Render();
    m_exitButton.Render();
    return true;
}

void PlayState::OnExit()
{
    m_inGame.OnExit();
}
