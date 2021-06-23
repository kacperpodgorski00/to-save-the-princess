#include "animationcomponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet)
    : sprite(sprite), textureSheet(texture_sheet), lastAnimation(nullptr), priorityAnimation(nullptr)
{

}

AnimationComponent::~AnimationComponent()
{
    for(auto &i : this->animations)
    {
        delete i.second;
    }
}

//Accessors
const bool & AnimationComponent::isDone(const std::string key)
{
    return this->animations[key]->isDone();
}

//Functions
void AnimationComponent::addAnimation(
    const std::string key,
    float animation_timer, int start_frame_x, int start_frame_y,
    int frames_x, int frames_y, int width, int height
)
{
    this->animations[key] = new Animation(
        this->sprite, this->textureSheet,
        animation_timer,
        start_frame_x, start_frame_y,
        frames_x, frames_y, width, height
    );
}

const bool & AnimationComponent::play(
        const std::string key, const float& delta_time, const bool priority)
{    
    if(this->priorityAnimation) //if there is a priority animation - play this
    {
        if(this->priorityAnimation == this->animations[key])
        {
            if(this->lastAnimation != this->animations[key])
            {
                if(this->lastAnimation == nullptr)
                {
                    this->lastAnimation = this->animations[key];
                }
                else
                {
                    this->lastAnimation->reset();
                    this->lastAnimation = this->animations[key];
                }

            }

            if(this->animations[key]->play(delta_time)) //if the priority animation is done, remove it
            {
                this->priorityAnimation = nullptr;
            }
        }
    }
    else //if there is not a priority animation - play this
    {
        if(priority) //if this is a priority animation - set it
        {
            this->priorityAnimation = this->animations[key];
        }

        if(this->lastAnimation != this->animations[key])
        {
            if(this->lastAnimation == nullptr)
            {
                this->lastAnimation = this->animations[key];
            }
            else
            {
                this->lastAnimation->reset();
                this->lastAnimation = this->animations[key];
            }

        }

        this->animations[key]->play(delta_time);
    }

    return this->animations[key]->isDone();
}

const bool & AnimationComponent::play(const std::string key, const float &delta_time,
                              const float &modifier, const float &modifier_max,
                              const bool priority)
{
    if(this->priorityAnimation) //if there is a priority animation - play this
    {
        if(this->priorityAnimation == this->animations[key])
        {
            if(this->lastAnimation != this->animations[key])
            {
                if(this->lastAnimation == nullptr)
                {
                    this->lastAnimation = this->animations[key];
                }
                else
                {
                    this->lastAnimation->reset();
                    this->lastAnimation = this->animations[key];
                }

            }

            this->animations[key]->play(delta_time, abs(modifier / modifier_max));
        }
    }
    else //if there is not a priority animation - play this
    {
        if(priority) //if this is a priority animation - set it
        {
            this->priorityAnimation = this->animations[key];
        }

        if(this->lastAnimation != this->animations[key])
        {
            if(this->lastAnimation == nullptr)
            {
                this->lastAnimation = this->animations[key];
            }
            else
            {
                this->lastAnimation->reset();
                this->lastAnimation = this->animations[key];
            }

        }

        this->animations[key]->play(delta_time, abs(modifier / modifier_max));//if the priority animation is done, remove it
    }

    return this->animations[key]->isDone();
}
