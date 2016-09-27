#include "BlockDrawer.h"



BlockDrawer::BlockDrawer( Board& board_, SDL_Renderer* renderer_) : board(board_), renderer(renderer_), nums(initialize_nums(renderer_))
{
	rect = std::make_unique<SDL_Rect>();
	SDL_Surface* temp = SDL_CreateRGBSurface(0, 70, 70, 32, 0, 0, 0, 0);
	set_rect(0, 0, 70, 70);
	SDL_FillRect(temp, rect.get(), SDL_MapRGB(temp->format, 50, 150, 255));
	_ASSERTE(temp != NULL);
	block_txt = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);
}


BlockDrawer::~BlockDrawer()
{
	SDL_DestroyTexture(block_txt);
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
		SDL_Surface* surf = TTF_RenderText_Solid(arial, std::to_string(i).c_str(), SDL_Color{255 , 255, 0 });
		nums_[i] = NumTexture(renderer_, surf);
		SDL_FreeSurface(surf);
	}
	return nums_;
}
void BlockDrawer::draw_block(int x, int y) {
	set_rect(leftOffset + (blockSize + spaceBetweenBlocks)*x, topOffset + (blockSize + spaceBetweenBlocks)*y, blockSize, blockSize);
	SDL_RenderCopy(renderer, block_txt, nullptr, rect.get());

	std::string str_num = std::to_string(board.getValueFrom(x,y));
	//hardcoded size
	int width = nums[0].w;
	int height = nums[0].h;
	int start_x = leftOffset + (blockSize + spaceBetweenBlocks)*x + blockSize / 2 - width*str_num.size() / 2;
	int start_y = topOffset + (blockSize + spaceBetweenBlocks)*y + blockSize / 2 - height / 2;
	set_rect(start_x, start_y, width, height);
	for (auto num : str_num) {
		SDL_RenderCopy(renderer, nums[num - '0'].texture, nullptr, rect.get());
		rect->x += width;
	}
	return;
}

void BlockDrawer::draw_points() {
	const int points_x = 180;
	const int points_y = 50;
	std::string str_points = std::to_string(board.get_points());
	int width = nums[0].w;
	int height = nums[0].h;
	int start_x = points_x - str_points.size() / 2 * width;
	int start_y = points_y - height / 2;
	set_rect(start_x, start_y, width, height);
	for (auto num : str_points) {
		SDL_RenderCopy(renderer, nums[num - '0'].texture, nullptr, rect.get());
		rect->x += width;
	}
	return;
}
