#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <algorithm>

struct being {
	double x, y;
	double f;
};

bool compare(const being& b1, const being& p2) {
	return b1.f > p2.f;
}

double f(double x, double y) {
	return -log(1 + x * x + y * y) + x * x / 2;
}

double x_y_rand(double x_y_Min, double x_y_Max) {
	double x_y = (double)rand() / RAND_MAX;
	return x_y_Min + x_y * (x_y_Max - x_y_Min);
}

std::vector<being> selection(std::vector<being>& population) {
	std::vector<being> intermediate_population = population;
	intermediate_population.pop_back();
	intermediate_population.pop_back();
	return intermediate_population;
}

std::vector<being> crossover(std::vector<being>& intermediate_population) {
	being b1;
	std::vector<being> new_population;
	b1.x = intermediate_population[0].x;
	b1.y = intermediate_population[1].y;
	b1.f = f(b1.x, b1.y);
	new_population.push_back(b1);

	b1.x = intermediate_population[1].x;
	b1.y = intermediate_population[0].y;
	b1.f = f(b1.x, b1.y);
	new_population.push_back(b1);

	b1.x = intermediate_population[0].x;
	b1.y = intermediate_population[2].y;
	b1.f = f(b1.x, b1.y);
	new_population.push_back(b1);

	b1.x = intermediate_population[2].x;
	b1.y = intermediate_population[0].y;
	b1.f = f(b1.x, b1.y);
	new_population.push_back(b1);

	b1.x = intermediate_population[0].x;
	b1.y = intermediate_population[3].y;
	b1.f = f(b1.x, b1.y);
	new_population.push_back(b1);

	b1.x = intermediate_population[3].x;
	b1.y = intermediate_population[0].y;
	b1.f = f(b1.x, b1.y);
	new_population.push_back(b1);

	return new_population;
}

void mutation(int j, std::vector<being>& new_population) {
	double tmp = new_population[j].y;
	new_population[j].y = new_population[j].x;
	new_population[j].x = tmp;
	new_population[j].f = f(new_population[j].x, new_population[j].y);
}

int main() {
	srand(time(NULL));
	being b1;
	std::vector<being> population;

	double average_f = 0;
	const int N = 10;
	const int population_size = 6;
	const double x1 = -1; const double x2 = 1; const double y1 = -1; const double y2 = 1;

	for (int i = 0; i < population_size; i++) {
		b1.x = x_y_rand(x1, x2);
		b1.y = x_y_rand(y1, y2);
		b1.f = f(b1.x, b1.y);
		population.push_back(b1);
	}

	std::sort(population.begin(), population.end(), compare);

	for (auto& i : population) {
		std::cout << "x = " << i.x << "    ";
		std::cout << "y = " << i.y << std::endl;
		std::cout << "f = " << i.f << std::endl;
		average_f += i.f;
	}
	average_f /= population_size;
	std::cout << "f_avg = " << average_f << std::endl;
	std::cout << "f_max = " << (*population.begin()).f << std::endl;

	std::vector<being> intermediate_population;
	std::vector<being> new_population;
	for (int i = 0; i < N; i++) {
		std::cout << i + 1 << std::endl << std::endl;

		intermediate_population = selection(population);

		new_population = crossover(intermediate_population);

		for (int j = 0; j < population_size; j++) {
			if ((rand() % 100 / 100.) <= 0.20) {
				mutation(j, new_population);
			}
		}

		average_f = 0;
		std::sort(new_population.begin(), new_population.end(), compare);
		for (auto& i : new_population) {
			std::cout << "x = " << i.x << "    ";
			std::cout << "y = " << i.y << std::endl;
			std::cout << "f = " << i.f << std::endl;
			average_f += i.f;
		}

		average_f /= population_size;
		population = new_population;
		std::cout << "f_avg = " << average_f << std::endl;
		std::cout << "f_max = " << (*population.begin()).f << std::endl << std::endl;
	}
	std::cout << "final_answer: f_max = " << (*population.begin()).f << std::endl;
}
