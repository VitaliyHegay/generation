clear
clc

% Имя файла для сохранения
filename = 'mixed_signal_M.wav';

% Параметры
Fs = 46 * 10^3;             % Частота дискретизации (Гц)
SNR = 60;              % Соотношение сигнал/шум в дБ

T = 2;                 % Длительность сигнала (с)
f_signal = 1 * 10^3;         % Частота сигнала (Гц)

% Время
t = 0:1/Fs:T-1/Fs;     % Вектор времени

% Генерация полезного сигнала (синусоидальный сигнал)
signal = sin(2*pi*f_signal*t);

% Генерация шума (белый гауссов шум)
noise = randn(size(t));

% Добавление шума к сигналу с заданным соотношением С/Ш
signal_power = bandpower(signal);  % Мощность сигнала
noise_power = signal_power / (10^(SNR/10));  % Необходимая мощность шума
noise = sqrt(noise_power) * noise;  % Масштабирование шума до нужного уровня

% Итоговая смесь
mixed_signal = signal + noise;

% spectr_m_s = fftshift(fft(mixed_signal));
% freqs = -Fs/2:Fs/length(mixed_signal):(Fs/2)-Fs/length(mixed_signal);
% 
% plot(freqs,abs(spectr_m_s));
% grid on
% 
% % Визуализация сигнала и смеси
% figure;
% subplot(3,1,1);
% plot(t, signal);
% title('Полезный сигнал');
% xlabel('Время (с)');
% ylabel('Амплитуда');
% 
% subplot(3,1,2);
% plot(t, noise);
% title('Шум');
% xlabel('Время (с)');
% ylabel('Амплитуда');
% 
% subplot(3,1,3);
% plot(t, mixed_signal);
% title('Сигнал + Шум');
% xlabel('Время (с)');
% ylabel('Амплитуда');

% Нормализация перед сохранением
mixed_signal = mixed_signal / max(abs(mixed_signal));  % Нормализация сигнала к диапазону [-1, 1]

sound(mixed_signal, Fs);

% Сохранение как WAV-файл
audiowrite(filename, mixed_signal, Fs);