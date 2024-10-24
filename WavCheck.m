clc
clear

% 1. Открыть wav-файл
[file, path] = uigetfile('*.wav', 'Выберите wav-файл');  % Диалоговое окно для выбора файла
filePath = fullfile(path, file);
[y, Fs] = audioread(filePath);  % Чтение аудиофайла

% 2. Построить график аудиосигнала
t = (0:length(y)-1)/Fs;  % Время для оси X
figure;
subplot(2,1,1);
plot(t, y);
xlabel('Время (с)');
ylabel('Амплитуда');
title('Аудиосигнал');
grid on;

% 3. Построить спектр сигнала
Y = fftshift(fft(y));  % Прямое преобразование Фурье
n = length(y);  % Количество точек данных
f = -Fs/2:Fs/n:Fs/2-Fs/n;  % Частоты для оси X\
subplot(2,1,2);
plot(f, abs(Y));
xlabel('Частота (Гц)');
ylabel('Амплитуда');
title('Спектр сигнала');
grid on;