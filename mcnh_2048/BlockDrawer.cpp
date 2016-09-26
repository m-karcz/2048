#include "BlockDrawer.h"



BlockDrawer::BlockDrawer(const Board& board_, SDL_Renderer* renderer_) : board(board_), renderer(renderer_), nums(initialize_nums(renderer_))
{
	rect = std::make_unique<SDL_Rect>();
}


BlockDrawer::~BlockDrawer()
{

}

void BlockDrawer::test_draw_nums(void)
{
	for (int i = 0; i < 10; i++) {
		/*([&](auto size) {set_rect(i * 20, i * 20, size.w, size.h);})(
			([&]() {
			int w, h;
			SDL_QueryTexture(nums[i], nullptr, nullptr, &w, &h);
			return Size{ w,h };
		})()
			);*/
		set_rect(i * 20, i * 20, nums[i].w, nums[i].h);
		_ASSERTE(nums[i].texture!=nullptr);
		SDL_RenderCopy(renderer, nums[i].texture, nullptr, rect.get());
		//		SDL_RenderCopy(renderer, nums[i].texture, nullptr, nullptr);

	}
}

void BlockDrawer::set_rect(int x, int y, int w, int h)
{
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
	return;
}

const std::array<NumTexture, 10> BlockDrawer::initialize_nums(SDL_Renderer * renderer_)
{
	std::array<NumTexture, 10> nums_;
	TTF_Font* arial = TTF_OpenFont("C:\\Windows\\Fonts\\arial.ttf", 24);
	for (int i = 0; i < 10; i++) {
		SDL_Surface* surf = TTF_RenderText_Solid(arial, std::to_string(i).c_str(), SDL_Color{100 , 255, 255 });
		nums_[i] = NumTexture(renderer_, surf);
		SDL_FreeSurface(surf);
	}
	return nums_;
}
