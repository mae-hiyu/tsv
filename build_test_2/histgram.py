import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

def read_spectra_data(filename):
    """
    指定されたファイルから波長とスペクトル強度を読み込む関数
    ファイルの形式は「波長 スペクトル強度」という2つの値がスペースで区切られていることを前提とする。
    """
    wavelengths = []
    intensities = []
    
    try:
        with open(filename, 'r') as file:
            for line in file:
                # 各行を波長とスペクトル強度に分割して読み込む
                parts = line.strip().split()
                if len(parts) == 2:
                    wavelength = int(parts[0])  # 波長
                    intensity = float(parts[1])  # スペクトル強度
                    wavelengths.append(wavelength)
                    intensities.append(intensity)
    except FileNotFoundError:
        print(f"{filename}が見つかりません")
    except ValueError:
        print("無効なデータが含まれています")
    
    return wavelengths, intensities

def update_histogram(frame):
    """
    アニメーションの各フレームでヒストグラムを更新するための関数
    """
    # 各ファイルのデータを読み込む
    x_wavelengths, x_intensities = read_spectra_data('xWavelength.txt')
    y_wavelengths, y_intensities = read_spectra_data('yWavelength.txt')
    z_wavelengths, z_intensities = read_spectra_data('zWavelength.txt')
    
    # データが空でない場合のみ更新
    if x_wavelengths and x_intensities and y_wavelengths and y_intensities and z_wavelengths and z_intensities:
        for ax, wavelengths, intensities, color, title in zip(
                axs, 
                [x_wavelengths, y_wavelengths, z_wavelengths],
                [x_intensities, y_intensities, z_intensities],
                ['red', 'green', 'blue'],
                ['X Histogram', 'Y Histogram', 'Z Histogram']):
            
            ax.clear()  # 現在のヒストグラムをクリア
            ax.bar(wavelengths, intensities, width=1.0, color=color, alpha=0.7)  # 棒グラフを描画
            ax.set_xlabel('Wavelength (nm)')
            ax.set_ylabel('Intensity')
            ax.set_title(title)
            ax.set_xlim(min(wavelengths), max(wavelengths))  # X軸の範囲を設定
            ax.set_ylim(0, max(intensities) * 1.1)  # Y軸の範囲を設定
    return axs

# プロット設定
fig, axs = plt.subplots(1, 3, figsize=(15, 5), tight_layout=True)  # 横に3つのプロット領域を作成

# アニメーション設定
ani = FuncAnimation(fig, update_histogram, interval=5000)  # 5秒ごとにヒストグラムを更新

# ヒストグラムを表示
plt.show()