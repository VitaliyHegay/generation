clear
clc

% Имя файла для сохранения
filename = 'melody_1_M.wav';

% Параметры
Fs = 44.1 * 10^3;                 % Частота дискретизации (Гц)
SNR = 60;                        % Соотношение сигнал/шум в дБ

% Параметры мелодии 1
Tn = [1.0, 0.5, 0.5, 1.0, 0.5, 0.5, 1.5, 1.0, 0.5, 0.5, 2.0, 1.0, 1.0, 1.5, 1.5, 2.0, 1.5, 1.0, 2.0];                                                                   % Длительность сигнала (с)
fn = [261.63, 329.63, 392.00, 523.25, 392.00, 329.63, 349.23, 293.66, 392.00, 493.88, 523.25, 440.00, 349.23, 329.63, 293.66, 261.63, 392.00, 329.63, 261.63];          % Частота сигнала (Гц)
An = ones(1, length(Tn));                                                                                                                                               % Амплитуды всех нот 1
T0n = [0.0, 1.0, 1.5, 2.0, 3.0, 3.5, 4.0, 5.5, 6.5, 7.0, 7.5, 9.5, 10.5, 11.5, 13.0, 14.5, 16.5, 18.0, 19.0];                                                           % Время начала сигнала (с)

% % Параметры мелодии 2
% Tn = [1.0, 0.5, 0.5, 1.5, 0.5, 0.5, 1.0, 1.0, 0.5, 0.5, 1.5, 0.5, 1.0, 2.0, 1.0, 2.0, 1.5, 1.0, 2.0];                                                                   % Длительность сигнала (с)
% fn = [392.00, 293.66, 329.63, 349.23, 392.00, 493.88, 523.25, 392.00, 349.23, 293.66, 392.00, 329.63, 349.23, 392.00, 440.00, 523.25, 293.66, 392.00, 261.63];          % Частота сигнала (Гц)
% An = [0.8, 0.6, 0.7, 1.0, 0.9, 0.8, 1.0, 0.7, 0.6, 0.9, 1.0, 0.7, 1.0, 0.9, 0.8, 1.0, 0.7, 1.0, 0.8];                                                                   % Амплитуды всех нот 1
% T0n = [0.0, 1.0, 1.5, 2.0, 3.5, 4.0, 4.5, 5.5, 6.5, 7.0, 7.5, 9.0, 9.5, 10.5, 12.5, 13.5, 15.5, 17.0, 18.0];                                                            % Время начала сигнала (с)

% Время всей "мелодии"
Time = T0n(length(T0n)) + Tn(length(Tn));
T = 0 : 1/Fs : Time-1/Fs;      % Вектор времени
signal = zeros(1, length(T));

for i = 1:length(fn)
    t = 0:1/Fs:Tn(i)-1/Fs;      % Вектор времени для каждой "ноты"

    note = An(i) * sin(2*pi * fn(i) * t);   % Генерация "ноты"

    sT0 = round(T0n(i) * Fs);          % Отсчет входа для каждой "ноты"

    signal(sT0+1:sT0+length(note)) = signal(sT0+1:sT0+length(note)) + note;
end

% Генерация шума (белый гауссов шум)
noise = randn(size(T));

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
% plot(T, signal);
% title('Полезный сигнал');
% xlabel('Время (с)');
% ylabel('Амплитуда');
% 
% subplot(3,1,2);
% plot(T, noise);
% title('Шум');
% xlabel('Время (с)');
% ylabel('Амплитуда');
% 
% subplot(3,1,3);
% plot(T, mixed_signal);
% title('Сигнал + Шум');
% xlabel('Время (с)');
% ylabel('Амплитуда');

% Нормализация перед сохранением
mixed_signal = mixed_signal / max(abs(mixed_signal));  % Нормализация сигнала к диапазону [-1, 1]

sound(mixed_signal, Fs);

% Сохранение как WAV-файл
audiowrite(filename, mixed_signal, Fs);