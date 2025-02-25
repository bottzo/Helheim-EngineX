#include "Sanity.h"

#include "Application.h"
#include "ModuleResource.h"
#include "ResourceTexture.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "ImageComponent.h"
#include "ButtonComponent.h"
#include "GameManager.h"
#include "PlayerController.h"
#include "AudioManager.h"
#include "ModuleInput.h"
#include "Keys.h"
#include "Transform2DComponent.h"
#include "ModuleScene.h"
#include "PlayerStats.h"

CREATE(Sanity)
{
    CLASS(owner);
    SEPARATOR("Cards");
    MEMBER(MemberType::GAMEOBJECT, mCard1GO);
    MEMBER(MemberType::GAMEOBJECT, mCard2GO);
    MEMBER(MemberType::GAMEOBJECT, mCard3GO);

    MEMBER(MemberType::GAMEOBJECT, mCard1Glow);
    MEMBER(MemberType::GAMEOBJECT, mCard2Glow);
    MEMBER(MemberType::GAMEOBJECT, mCard3Glow);
    MEMBER(MemberType::GAMEOBJECT, mCard1Selected);
    MEMBER(MemberType::GAMEOBJECT, mCard2Selected);
    MEMBER(MemberType::GAMEOBJECT, mCard3Selected);

    SEPARATOR("Speed Box");
    MEMBER(MemberType::GAMEOBJECT, mSpeedBox1);
    MEMBER(MemberType::GAMEOBJECT, mSpeedBox2);
    MEMBER(MemberType::GAMEOBJECT, mSpeedBox3);
    MEMBER(MemberType::GAMEOBJECT, mSpeedBox4);
    MEMBER(MemberType::GAMEOBJECT, mSpeedBox5);
    MEMBER(MemberType::GAMEOBJECT, mSpeedBox6);
    MEMBER(MemberType::GAMEOBJECT, mSpeedBox7);
    MEMBER(MemberType::GAMEOBJECT, mSpeedBox1Selected);
    MEMBER(MemberType::GAMEOBJECT, mSpeedBox2Selected);
    MEMBER(MemberType::GAMEOBJECT, mSpeedBox3Selected);
    MEMBER(MemberType::GAMEOBJECT, mSpeedBox4Selected);
    MEMBER(MemberType::GAMEOBJECT, mSpeedBox5Selected);
    MEMBER(MemberType::GAMEOBJECT, mSpeedBox6Selected);
    MEMBER(MemberType::GAMEOBJECT, mSpeedBox7Selected);

    SEPARATOR("Health Box");
    MEMBER(MemberType::GAMEOBJECT, mHealthBox1);
    MEMBER(MemberType::GAMEOBJECT, mHealthBox2);
    MEMBER(MemberType::GAMEOBJECT, mHealthBox3);
    MEMBER(MemberType::GAMEOBJECT, mHealthBox4);
    MEMBER(MemberType::GAMEOBJECT, mHealthBox5);
    MEMBER(MemberType::GAMEOBJECT, mHealthBox6);
    MEMBER(MemberType::GAMEOBJECT, mHealthBox7);
    MEMBER(MemberType::GAMEOBJECT, mHealthBox1Selected);
    MEMBER(MemberType::GAMEOBJECT, mHealthBox2Selected);
    MEMBER(MemberType::GAMEOBJECT, mHealthBox3Selected);
    MEMBER(MemberType::GAMEOBJECT, mHealthBox4Selected);
    MEMBER(MemberType::GAMEOBJECT, mHealthBox5Selected);
    MEMBER(MemberType::GAMEOBJECT, mHealthBox6Selected);
    MEMBER(MemberType::GAMEOBJECT, mHealthBox7Selected);

    SEPARATOR("Damage Box");
    MEMBER(MemberType::GAMEOBJECT, mDmgBox1);
    MEMBER(MemberType::GAMEOBJECT, mDmgBox2);
    MEMBER(MemberType::GAMEOBJECT, mDmgBox3);
    MEMBER(MemberType::GAMEOBJECT, mDmgBox4);
    MEMBER(MemberType::GAMEOBJECT, mDmgBox5);
    MEMBER(MemberType::GAMEOBJECT, mDmgBox6);
    MEMBER(MemberType::GAMEOBJECT, mDmgBox7);
    MEMBER(MemberType::GAMEOBJECT, mDmgBox1Selected);
    MEMBER(MemberType::GAMEOBJECT, mDmgBox2Selected);
    MEMBER(MemberType::GAMEOBJECT, mDmgBox3Selected);
    MEMBER(MemberType::GAMEOBJECT, mDmgBox4Selected);
    MEMBER(MemberType::GAMEOBJECT, mDmgBox5Selected);
    MEMBER(MemberType::GAMEOBJECT, mDmgBox6Selected);
    MEMBER(MemberType::GAMEOBJECT, mDmgBox7Selected);

    END_CREATE;
}

Sanity::Sanity(GameObject* owner) : Script(owner)
{
    // Create buff selections
    mBuffSelection.push_back({ Buff(Buff::StatType::DAMAGE, 1.1f), Buff(Buff::StatType::MOVEMENT, 1.10f), Buff(Buff::StatType::HEALTH, 1.10f) });
    mBuffSelection.push_back({ Buff(Buff::StatType::DAMAGE, 1.1f), Buff(Buff::StatType::MOVEMENT, 1.10f), Buff(Buff::StatType::HEALTH, 1.10f) });
    mBuffSelection.push_back({ Buff(Buff::StatType::DAMAGE, 1.1f), Buff(Buff::StatType::MOVEMENT, 1.10f), Buff(Buff::StatType::HEALTH, 1.10f) });
    mBuffSelection.push_back({ Buff(Buff::StatType::DAMAGE, 1.15f), Buff(Buff::StatType::MOVEMENT, 1.15f), Buff(Buff::StatType::HEALTH, 1.15f) });
    mBuffSelection.push_back({ Buff(Buff::StatType::DAMAGE, 1.15f), Buff(Buff::StatType::MOVEMENT, 1.15f), Buff(Buff::StatType::HEALTH, 1.15f) });
    mBuffSelection.push_back({ Buff(Buff::StatType::DAMAGE, 1.20f), Buff(Buff::StatType::MOVEMENT, 1.20f), Buff(Buff::StatType::HEALTH, 1.20f) });
    mBuffSelection.push_back({ Buff(Buff::StatType::DAMAGE, 1.20f), Buff(Buff::StatType::MOVEMENT, 1.20f), Buff(Buff::StatType::HEALTH, 1.20f) });
    mBuffSelection.push_back({ Buff(Buff::StatType::DAMAGE, 1.20f), Buff(Buff::StatType::MOVEMENT, 1.20f), Buff(Buff::StatType::HEALTH, 1.20f) });
}

Sanity::~Sanity()
{
}

void Sanity::Start()
{
    if (mCard1GO)
    {
        const std::vector<GameObject*> children1 = mCard1GO->GetChildren();
        mCard1Text = static_cast<TextComponent*>(children1[4]->GetComponent(ComponentType::TEXT));
        mCard1Btn = static_cast<ButtonComponent*>(children1[2]->GetComponent(ComponentType::BUTTON));
        mCard1Image = static_cast<ImageComponent*>(children1[2]->GetComponent(ComponentType::IMAGE));
        mCard1Icon = static_cast<ImageComponent*>(children1[5]->GetComponent(ComponentType::IMAGE));
        mCard1Hover = children1[0];
        mCard1Btn->AddEventHandler(EventType::CLICK, new std::function<void()>(std::bind(&Sanity::OnCard1Click, this)));
        mCard1Btn->AddEventHandler(EventType::HOVER, new std::function<void()>(std::bind(&Sanity::OnCard1HoverOn, this)));
        mCard1Btn->AddEventHandler(EventType::HOVEROFF, new std::function<void()>(std::bind(&Sanity::OnCard1HoverOff, this)));
    }
    
    if (mCard2GO)
    {
        const std::vector<GameObject*> children2 = mCard2GO->GetChildren();
        mCard2Text = static_cast<TextComponent*>(children2[4]->GetComponent(ComponentType::TEXT));
        mCard2Btn = static_cast<ButtonComponent*>(children2[2]->GetComponent(ComponentType::BUTTON));
        mCard2Image = static_cast<ImageComponent*>(children2[2]->GetComponent(ComponentType::IMAGE));
        mCard2Icon = static_cast<ImageComponent*>(children2[5]->GetComponent(ComponentType::IMAGE));
        mCard2Hover = children2[0];
        mCard2Btn->AddEventHandler(EventType::CLICK, new std::function<void()>(std::bind(&Sanity::OnCard2Click, this)));
        mCard2Btn->AddEventHandler(EventType::HOVER, new std::function<void()>(std::bind(&Sanity::OnCard2HoverOn, this)));
        mCard2Btn->AddEventHandler(EventType::HOVEROFF, new std::function<void()>(std::bind(&Sanity::OnCard2HoverOff, this)));
    }

    if (mCard3GO)
    {
        const std::vector<GameObject*> children3 = mCard3GO->GetChildren();
        mCard3Text = static_cast<TextComponent*>(children3[4]->GetComponent(ComponentType::TEXT));
        mCard3Btn = static_cast<ButtonComponent*>(children3[2]->GetComponent(ComponentType::BUTTON));
        mCard3Image = static_cast<ImageComponent*>(children3[2]->GetComponent(ComponentType::IMAGE));
        mCard3Icon = static_cast<ImageComponent*>(children3[5]->GetComponent(ComponentType::IMAGE));
        mCard3Hover = children3[0];
        mCard3Btn->AddEventHandler(EventType::CLICK, new std::function<void()>(std::bind(&Sanity::OnCard3Click, this)));
        mCard3Btn->AddEventHandler(EventType::HOVER, new std::function<void()>(std::bind(&Sanity::OnCard3HoverOn, this)));
        mCard3Btn->AddEventHandler(EventType::HOVEROFF, new std::function<void()>(std::bind(&Sanity::OnCard3HoverOff, this)));
    }

    CreateSelection(0);

    mHealthLvl = App->GetScene()->GetPlayerStats()->GetHealthLvl();
    mSpeedLvl = App->GetScene()->GetPlayerStats()->GetSpeedLvl();
    mDmgLvl = App->GetScene()->GetPlayerStats()->GetDamageLvl();
    SetDamageBoxes();
    SetHealthBoxes();
    SetSpeedBoxes();
}

void Sanity::Update()
{
    if (mEnd && mEndTimer.Delay(0.0f)) FinishSanity();
    //else if (mEnd) UpdateSelected();

    Controls();

    if (mTimeout && mClickTimout.Delay(0.5f))
    {
        mTimeout = false;
        mCurrentBuff = 2;
        CardHover();
    }
    mTimePassed += App->GetDt();
}

void Sanity::Controls() 
{
    if (mTimeout) return;
    if (App->GetInput()->GetKey(Keys::Keys_RIGHT) == KeyState::KEY_DOWN ||
        App->GetInput()->GetGameControllerButton(ControllerButton::SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == ButtonState::BUTTON_DOWN || ((App->GetInput()->GetGameControllerAxisValue(ControllerAxis::SDL_CONTROLLER_AXIS_LEFTX) > 0.9f && mTimePassed >= mDebounceTime)))
    {
        GameManager::GetInstance()->GetAudio()->PlayOneShot(SFX::MAINMENU_SELECT);

        mTimePassed = 0.0f; // Restart debounce timer

        if (mCurrentBuff == 0)
        {
            mCurrentBuff = 2;
        }
        else
        {
            mCurrentBuff--;
        }
        CardHover();
    }

    if (App->GetInput()->GetKey(Keys::Keys_LEFT) == KeyState::KEY_DOWN ||
        App->GetInput()->GetGameControllerButton(ControllerButton::SDL_CONTROLLER_BUTTON_DPAD_LEFT) == ButtonState::BUTTON_DOWN || ((App->GetInput()->GetGameControllerAxisValue(ControllerAxis::SDL_CONTROLLER_AXIS_LEFTX) < -0.9f && mTimePassed >= mDebounceTime)))
    {
        GameManager::GetInstance()->GetAudio()->PlayOneShot(SFX::MAINMENU_SELECT);

        mTimePassed = 0.0f; // Restart debounce timer

        if (mCurrentBuff > 1)
        {
            mCurrentBuff = 0;
        }
        else
        {
            mCurrentBuff++;
        }
        CardHover();
    }

    if (App->GetInput()->GetKey(Keys::Keys_RETURN) == KeyState::KEY_DOWN ||
        App->GetInput()->GetKey(Keys::Keys_KP_ENTER) == KeyState::KEY_DOWN ||
        App->GetInput()->GetGameControllerButton(ControllerButton::SDL_CONTROLLER_BUTTON_A) == ButtonState::BUTTON_DOWN)
    {
        GameManager::GetInstance()->GetAudio()->PlayOneShot(SFX::MAINMENU_OK);

        CardClick();
    }
}

void Sanity::CreateSelection(int arena)
{
    if (arena < 0 || arena >= mBuffSelection.size()) return;

    ResetSelected();
    mEnd = false;

    GameManager::GetInstance()->SetPaused(true, false);
    
    mTimeout = true;
    CardHover();

    mCurrentBuffs = mBuffSelection[arena];

    // Card 1
    if (!mCurrentBuffs.empty())
    {
        Buff buff1 = mCurrentBuffs[0];
        mCard1Text->SetText(GetBuffDescription(buff1));
    }

    // Card 2
    if (mCurrentBuffs.size() > 1)
    {
        Buff buff2 = mCurrentBuffs[1];
        mCard2Text->SetText(GetBuffDescription(buff2));
    }

    // Card 3
    if (mCurrentBuffs.size() > 2)
    {
        Buff buff3 = mCurrentBuffs[2];
        mCard3Text->SetText(GetBuffDescription(buff3));
    }
}

std::string Sanity::GetBuffDescription(const Buff& buff)
{
    switch (buff.getStatType())
    {
        case Buff::StatType::MOVEMENT:
            return "SPEED +" + std::to_string(((int)((buff.getValue()-1)*100))) + "%";
        case Buff::StatType::DAMAGE:
            return "DAMAGE +" + std::to_string(((int)((buff.getValue() - 1) * 100))) + "%";
        case Buff::StatType::HEALTH:
            return "HEALTH +" + std::to_string(((int)((buff.getValue() - 1) * 100))) + "%";
        default:
            return "";
    }
}

void Sanity::FinishSanity()
{
    mGameObject->SetEnabled(false);
    GameManager::GetInstance()->SetPaused(false, false);
}

void Sanity::CardClick()
{
    if (mEnd) return;
    switch (mCurrentBuff)
    {
        case 0:
            OnCard1Click();
            break;
        case 1:
            OnCard2Click();
            break;
        case 2:
            OnCard3Click();
            break;
        default:
            break;
    }
}

void Sanity::CardHover()
{
    if (mEnd) return;
    switch (mCurrentBuff)
    {
    case 0:
        OnCard1HoverOn();
        break;
    case 1:
        OnCard2HoverOn();
        break;
    case 2:
        OnCard3HoverOn();
        break;
    default:
        break;
    }
}

void Buff::Consume()
{
    switch (stat) 
    {
        case Buff::StatType::MOVEMENT:
            GameManager::GetInstance()->GetPlayerController()->SetMovementSpeedStat(value);
            break;
        case Buff::StatType::DAMAGE:
            GameManager::GetInstance()->GetPlayerController()->SetWeaponDamage(value);
            break;
        case Buff::StatType::HEALTH:
            GameManager::GetInstance()->GetPlayerController()->SetMaxShield(value);
            break;
        default:
            break;
    }
}

void Sanity::OnCard1Click()
{
    if (mEnd) return;
    if (mTimeout) return;

    GameManager::GetInstance()->GetAudio()->PlayOneShot(SFX::MAINMENU_OK);

    if (!mCurrentBuffs.empty())
        mCurrentBuffs.at(0).Consume();

    mDmgLvl++;
    SetDamageBoxes();
    App->GetScene()->GetPlayerStats()->SetDamageLvl(mDmgLvl);

    mCard1Glow->SetEnabled(true);
    mCard1Selected->SetEnabled(true);
    SetDamageBoxesSelected(mDmgLvl);
    mCard2Image->SetAlpha(0.5f);
    mCard2Icon->SetAlpha(0.5f);
    mCard3Image->SetAlpha(0.5f);
    mCard3Icon->SetAlpha(0.5f);

    mEnd = true;
}

void Sanity::OnCard1HoverOn()
{
    if (mEnd) return;
    if (mTimeout) return;
    if (mCard1Hovered) return;
    mCard1Hovered = true;

    OnCard1HoverOff();
    OnCard2HoverOff();
    OnCard3HoverOff();

    mCard1Image->SetAlpha(1.0f);
    mCard1Icon->SetAlpha(1.0f);
    mCard1Hover->SetEnabled(true);
    GameManager::GetInstance()->GetAudio()->PlayOneShot(SFX::MAINMENU_SELECT);
}

void Sanity::OnCard1HoverOff()
{
    if (mEnd) return;
    mCard1Hovered = false;
    mCard1Image->SetAlpha(0.7f);
    mCard1Icon->SetAlpha(0.7f);
    mCard1Hover->SetEnabled(false);
}

void Sanity::OnCard2Click()
{
    if (mEnd) return;
    if (mTimeout) return;

    GameManager::GetInstance()->GetAudio()->PlayOneShot(SFX::MAINMENU_OK);

    if (mCurrentBuffs.size() > 1)
        mCurrentBuffs.at(1).Consume();
    
    mSpeedLvl++;
    SetSpeedBoxes();
    App->GetScene()->GetPlayerStats()->SetSpeedLvl(mSpeedLvl);

    mCard2Glow->SetEnabled(true);
    mCard2Selected->SetEnabled(true);
    SetSpeedBoxesSelected(mSpeedLvl);
    mCard1Image->SetAlpha(0.5f);
    mCard1Icon->SetAlpha(0.5f);
    mCard3Image->SetAlpha(0.5f);
    mCard3Icon->SetAlpha(0.5f);

    mEnd = true;
}

void Sanity::OnCard2HoverOn()
{
    if (mEnd) return;
    if (mTimeout) return;
    if (mCard2Hovered) return;
    mCard2Hovered = true;

    OnCard1HoverOff();
    OnCard2HoverOff();
    OnCard3HoverOff();

    mCard2Image->SetAlpha(1.0f);
    mCard2Icon->SetAlpha(1.0f);
    mCard2Hover->SetEnabled(true);
    GameManager::GetInstance()->GetAudio()->PlayOneShot(SFX::MAINMENU_SELECT);
}

void Sanity::OnCard2HoverOff()
{
    if (mEnd) return;
    mCard2Hovered = false;
    mCard2Image->SetAlpha(0.7f);
    mCard2Icon->SetAlpha(0.7f);
    mCard2Hover->SetEnabled(false);
}

void Sanity::OnCard3Click()
{
    if (mEnd) return;
    if (mTimeout) return;

    GameManager::GetInstance()->GetAudio()->PlayOneShot(SFX::MAINMENU_OK);

    if (mCurrentBuffs.size() > 2)
        mCurrentBuffs.at(2).Consume();

    mHealthLvl++;
    SetHealthBoxes();
    App->GetScene()->GetPlayerStats()->SetHealthLvl(mHealthLvl);

    mCard3Glow->SetEnabled(true);
    mCard3Selected->SetEnabled(true);
    SetHealthBoxesSelected(mHealthLvl);
    mCard1Image->SetAlpha(0.5f);
    mCard1Icon->SetAlpha(0.5f);
    mCard2Image->SetAlpha(0.5f);
    mCard2Icon->SetAlpha(0.5f);

    mEnd = true;
}

void Sanity::OnCard3HoverOn()
{
    if (mEnd) return;
    if (mTimeout) return;
    if (mCard3Hovered) return;
    mCard3Hovered = true;

    OnCard1HoverOff();
    OnCard2HoverOff();
    OnCard3HoverOff();

    mCard3Image->SetAlpha(1.0f);
    mCard3Icon->SetAlpha(1.0f);
    mCard3Hover->SetEnabled(true);
    GameManager::GetInstance()->GetAudio()->PlayOneShot(SFX::MAINMENU_SELECT);
}

void Sanity::OnCard3HoverOff()
{
    if (mEnd) return;
    mCard3Image->SetAlpha(0.7f);
    mCard3Icon->SetAlpha(0.7f);
    mCard3Hovered = false;
    mCard3Hover->SetEnabled(false);
}

void Sanity::SetSpeedBoxes()
{
    switch (mSpeedLvl)
    {
        case 7:
            mSpeedBox7->SetEnabled(true);
            [[fallthrough]];
        case 6:
            mSpeedBox6->SetEnabled(true);
            [[fallthrough]];
        case 5:
            mSpeedBox5->SetEnabled(true);
            [[fallthrough]];
        case 4:
            mSpeedBox4->SetEnabled(true);
            [[fallthrough]];
        case 3:
            mSpeedBox3->SetEnabled(true);
            [[fallthrough]];
        case 2:
            mSpeedBox2->SetEnabled(true);
            [[fallthrough]];
        case 1:
            mSpeedBox1->SetEnabled(true);
            [[fallthrough]];
        default:
            break;
    }
}

void Sanity::SetHealthBoxes()
{
    switch (mHealthLvl)
    {
    case 7:
        mHealthBox7->SetEnabled(true);
        [[fallthrough]];
    case 6:
        mHealthBox6->SetEnabled(true);
        [[fallthrough]];
    case 5:
        mHealthBox5->SetEnabled(true);
        [[fallthrough]];
    case 4:
        mHealthBox4->SetEnabled(true);
        [[fallthrough]];
    case 3:
        mHealthBox3->SetEnabled(true);
        [[fallthrough]];
    case 2:
        mHealthBox2->SetEnabled(true);
        [[fallthrough]];
    case 1:
        mHealthBox1->SetEnabled(true);
        [[fallthrough]];
    default:
        break;
    }
}

void Sanity::SetDamageBoxes()
{
    switch (mDmgLvl)
    {
    case 7:
        mDmgBox7->SetEnabled(true);
        [[fallthrough]];
    case 6:
        mDmgBox6->SetEnabled(true);
        [[fallthrough]];
    case 5:
        mDmgBox5->SetEnabled(true);
        [[fallthrough]];
    case 4:
        mDmgBox4->SetEnabled(true);
        [[fallthrough]];
    case 3:
        mDmgBox3->SetEnabled(true);
        [[fallthrough]];
    case 2:
        mDmgBox2->SetEnabled(true);
        [[fallthrough]];
    case 1:
        mDmgBox1->SetEnabled(true);
        [[fallthrough]];
    default:
        break;
    }
}

void Sanity::SetSpeedBoxesSelected(int value)
{
    switch (value)
    {
    case 7:
        mSpeedBox7Selected->SetEnabled(true);
        mSelected = mSpeedBox7Selected;
        break;
    case 6:
        mSpeedBox6Selected->SetEnabled(true);
        mSelected = mSpeedBox6Selected;
        break;
    case 5:
        mSpeedBox5Selected->SetEnabled(true);
        mSelected = mSpeedBox5Selected;
        break;
    case 4:
        mSpeedBox4Selected->SetEnabled(true);
        mSelected = mSpeedBox4Selected;
        break;
    case 3:
        mSpeedBox3Selected->SetEnabled(true);
        mSelected = mSpeedBox3Selected;
        break;
    case 2:
        mSpeedBox2Selected->SetEnabled(true);
        mSelected = mSpeedBox2Selected;
        break;
    case 1:
        mSpeedBox1Selected->SetEnabled(true);
        mSelected = mSpeedBox1Selected;
        break;
    default:
        break;
    }
}

void Sanity::SetHealthBoxesSelected(int value)
{
    switch (value)
    {
    case 7:
        mHealthBox7Selected->SetEnabled(true);
        mSelected = mHealthBox7Selected;
        break;
    case 6:
        mHealthBox6Selected->SetEnabled(true);
        mSelected = mHealthBox6Selected;
        break;
    case 5:
        mHealthBox5Selected->SetEnabled(true);
        mSelected = mHealthBox5Selected;
        break;
    case 4:
        mHealthBox4Selected->SetEnabled(true);
        mSelected = mHealthBox4Selected;
        break;
    case 3:
        mHealthBox3Selected->SetEnabled(true);
        mSelected = mHealthBox3Selected;
        break;
    case 2:
        mHealthBox2Selected->SetEnabled(true);
        mSelected = mHealthBox2Selected;
        break;
    case 1:
        mHealthBox1Selected->SetEnabled(true);
        mSelected = mHealthBox1Selected;
        break;
    default:
        break;
    }
}

void Sanity::SetDamageBoxesSelected(int value)
{
    switch (value)
    {
    case 7:
        mDmgBox7Selected->SetEnabled(true);
        mSelected = mDmgBox7Selected;
        break;
    case 6:
        mDmgBox6Selected->SetEnabled(true);
        mSelected = mDmgBox6Selected;
        break;
    case 5:
        mDmgBox5Selected->SetEnabled(true);
        mSelected = mDmgBox5Selected;
        break;
    case 4:
        mDmgBox4Selected->SetEnabled(true);
        mSelected = mDmgBox4Selected;
        break;
    case 3:
        mDmgBox3Selected->SetEnabled(true);
        mSelected = mDmgBox3Selected;
        break;
    case 2:
        mDmgBox2Selected->SetEnabled(true);
        mSelected = mDmgBox2Selected;
        break;
    case 1:
        mDmgBox1Selected->SetEnabled(true);
        mSelected = mDmgBox1Selected;
        break;
    default:
        break;
    }
}

void Sanity::ResetSelected()
{
    mSelected = nullptr;
    mSelectedImage = nullptr;

    mCard1Image->SetAlpha(0.7f);
    mCard1Icon->SetAlpha(0.7f);
    mCard2Image->SetAlpha(0.7f);
    mCard2Icon->SetAlpha(0.7f);
    mCard3Image->SetAlpha(0.7f);
    mCard3Icon->SetAlpha(0.7f);

    mCard1Glow->SetEnabled(false);
    mCard1Selected->SetEnabled(false);
    mCard2Glow->SetEnabled(false);
    mCard2Selected->SetEnabled(false);
    mCard3Glow->SetEnabled(false);
    mCard3Selected->SetEnabled(false);


    mDmgBox7Selected->SetEnabled(false);
    mDmgBox6Selected->SetEnabled(false);
    mDmgBox5Selected->SetEnabled(false);
    mDmgBox4Selected->SetEnabled(false);
    mDmgBox3Selected->SetEnabled(false);
    mDmgBox2Selected->SetEnabled(false);
    mDmgBox1Selected->SetEnabled(false);

    mHealthBox7Selected->SetEnabled(false);
    mHealthBox6Selected->SetEnabled(false);
    mHealthBox5Selected->SetEnabled(false);
    mHealthBox4Selected->SetEnabled(false);
    mHealthBox3Selected->SetEnabled(false);
    mHealthBox2Selected->SetEnabled(false);
    mHealthBox1Selected->SetEnabled(false);

    mSpeedBox7Selected->SetEnabled(false);
    mSpeedBox6Selected->SetEnabled(false);
    mSpeedBox5Selected->SetEnabled(false);
    mSpeedBox4Selected->SetEnabled(false);
    mSpeedBox3Selected->SetEnabled(false);
    mSpeedBox2Selected->SetEnabled(false);
    mSpeedBox1Selected->SetEnabled(false);
}

/*void Sanity::UpdateSelected()
{
    if (!mSelectedImage)
    {
        mSelectedImage = static_cast<ImageComponent*>(mSelected->GetComponent(ComponentType::IMAGE));
        mSelectedImage->SetAlpha(1.0f);
    }

    if(*mSelectedImage->GetAlpha() > 0.0f) mSelectedImage->SetAlpha(*mSelectedImage->GetAlpha() - 0.1f * App->GetDt());
}*/
