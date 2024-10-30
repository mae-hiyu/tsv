import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

def read_spectra_data(filename):
    """
    output.txtから波長とスペクトル強度を読み込む関数
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
    # output.txtのデータを読み込む
    wavelengths, intensities = read_spectra_data('output.txt')
    
    # データが空でない場合のみ更新
    if wavelengths and intensities:
        ax.clear()  # 現在のヒストグラムをクリア
        ax.bar(wavelengths, intensities, width=1.0, color='red', alpha=0.7)  # 棒グラフを描画
        ax.set_xlabel('Wavelength (nm)')
        ax.set_ylabel('Intensity')
        ax.set_title('Real-time Spectra Histogram')
        ax.set_xlim(min(wavelengths), max(wavelengths))  # X軸の範囲を設定
    return ax,

# プロット設定
fig, ax = plt.subplots()

# アニメーション設定
ani = FuncAnimation(fig, update_histogram, interval=5000)  # 5秒ごとにヒストグラムを更新

# ヒストグラムを表示
plt.show()