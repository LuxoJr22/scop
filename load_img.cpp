#include "utils.hpp"

int hex_to_int(std::string hex)
{
	int ret;

	if (hex[0] > 64)
		ret = hex[0] - 55;
	else
		ret = hex[0] - 48;

	ret *= 16;

	if (hex[1] > 64)
		ret += hex[1] - 55;
	else
		ret += hex[1] - 48;

	return ret;
}

colors	color_parsing(std::string col)
{
	colors	color;

	color.r = 255;
	color.g = 255;
	color.b = 255;

	color.r = hex_to_int(col.substr(0, 2));
	color.g = hex_to_int(col.substr(2, 2));
	color.b = hex_to_int(col.substr(4, 2));
	color.a = 255;

	return (color);
}

std::string fill_char(std::string act_line, img_load *img)
{
	std::string chars;
	std::string color_string;
	colors		color;

	chars = act_line.substr(0, act_line.find('	'));

	color_string = act_line.substr(act_line.find_last_of('#') + 1, act_line.length());
	color = color_parsing(color_string);

	img->chars[chars] = color;

	return (act_line);
}

int fill_img(std::string act_line, img_load *img, int act_px)
{
	std::string	pixels_char;

	while (act_line.length() >= img->len_char)
	{
		pixels_char = act_line.substr(0, img->len_char);
		img->pixels[act_px] = char(img->chars[pixels_char].r);
		img->pixels[act_px + 1] = char(img->chars[pixels_char].g);
		img->pixels[act_px + 2] = char(img->chars[pixels_char].b);
		img->pixels[act_px + 3] = char(img->chars[pixels_char].a);
		
		act_px += 4;

		act_line = act_line.substr(img->len_char, act_line.length());
	}
	img->pixels[act_px] = '\0';

	return (act_px);
}

std::array<float, 4> split_line(std::string line)
{
	std::string	act_line;
	std::array<float, 4> number;
	int i = 0;

	act_line = line;
	while (act_line.find(' ') != std::string::npos)
	{
		if (i != 0)
			act_line = act_line.substr(act_line.find(' ') + 1, act_line.length());
		number[i] = atof(act_line.substr(0, act_line.find(' ')).c_str());
		
		i ++;
	}
	return (number);
}

void fill_struct(img_load *img, std::string line)
{
	std::array<float, 4> numb;

	numb = split_line(line);

	img->width = numb[0];
	img->height = numb[1];
	img->nb_char = numb[2];
	img->len_char = numb[3];

}

unsigned char *load_img(const char *str, int *width, int *height)
{
	std::ifstream file;
	std::string	line;
	img_load	img;

	int i = 0;
	int act_px = 0;


	file.open(str);

	

	if (file.good())
	{
		getline(file, line);
		getline(file, line);

		getline(file, line);
		line = line.substr(line.find_first_of('"') + 1, line.find_last_of('"') - 1);
		fill_struct(&img, line);
		
		while (i < img.nb_char && getline(file, line)) {
			line = line.substr(line.find_first_of('"') + 1, line.find_last_of('"') - 1);
			fill_char(line, &img);
			i ++;
		}
		i = 0;
		img.pixels = (unsigned char *)malloc(sizeof(unsigned char) * ((img.width * img.height * 4) + 1));
		img.pixels[0] = '\0';
		
		while (getline(file, line) && i < img.height) {
			line = line.substr(line.find_first_of('"') + 1, line.find_last_of('"') - 1);
			act_px = fill_img(line, &img, act_px);
			i ++;
		}
	}
	*width = img.width;
	*height = img.height;
	file.close();
	return (img.pixels);
}