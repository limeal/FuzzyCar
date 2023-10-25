from tensorflow import keras
from keras import models
from keras import layers
from tensorflow.python.keras.backend import relu, sigmoid
from tensorflow.python.keras.models import Sequential
from ReplayMemory import ReplayMemory
import numpy as np
from ReplayMemory import ReplayMemory


class DQNAgent(object):
    def __init__(self, batch_size=100, gamma=0.9):
        # 학습에 사용될 모델
        self.model = self._create_model()
        # 타겟 모델
        self.target_model = self._create_model()
        self.target_model.set_weights(self.model.get_weights())  # 둘다 같은 weight로 설정

        self.replayMemory = ReplayMemory()
        self.gamma = gamma  # discount factor
        self.batch_size = batch_size
        self.callbacks = [
            keras.callbacks.TensorBoard(
                log_dir="my_log_dir",
                histogram_freq=1,
                embeddings_freq=1,
            )
        ]

    def _create_model(self) -> Sequential:
        model = models.Sequential()
        # input으로 6칸의 정보를 받는다
        model.add(layers.Dense(128, activation=relu, input_shape=(6,)))
        model.add(layers.Dense(64, activation=relu))
        model.add(layers.Dense(3))
        model.compile(optimizer="adam", loss="mse")  # , metrics=['mse']로 손실 기록?
        return model

    def forward(self, data):
        return self.model.predict(data)

    # Replay Memory를 이용해서 Agent를 학습
    def train(self):
        # replayMemory에 저장된 experience의 개수는 2000개 이상이어야 함
        if 2000 > len(self.replayMemory):
            return

        # batch_size만큼 샘플링한다
        # (cur_state, action, reward, done, info, next_state) : list
        samples = self.replayMemory.sample(self.batch_size)
        # batch data를 생성한다

        current_states = np.stack([sample[0] for sample in samples])
        current_q = self.model.predict(current_states)
        next_states = np.stack([sample[5] for sample in samples]) # 4??
        next_q = self.target_model.predict(next_states)

        for i, (cur_state, action, reward, done, info, next_state) in enumerate(
            samples
        ):
            if done:
                next_q_value = reward
            else:
                next_q_value = reward + self.gamma * np.max(next_q[i])
            current_q[i][action] = next_q_value

        # 학습!!
        self.model.fit(
            x=current_states,
            y=current_q,
            batch_size=self.batch_size,
            verbose=False,
        )

    # target model의 가중치를 model의 가중치로 update 한다
    def _update_target_model(self):
        self.target_model.set_weights(self.model.get_weights())

    # ------------------------------------------------------------#
    """
    def save(
        self,
        path: str,
        model_name: str,
        version: str,
        num_trained: int,
        target_model_name: str = None,
    ):
        
        #모델 저장 이름 예시
        #/path/fuzzycar_v5_300_trained.h5

        
        save_name = f"{path}/{model_name}_{version}_{num_trained}_trained.h5"
        target_model_name = f"target_{model_name}"
        target_save_name = (
            f"{path}/{target_model_name}_{version}_{num_trained}_trained.h5"
        )
        self.model.save(save_name)
        self.target_model.save(target_save_name)

    def load(
        self,
        path: str,
        model_name: str,
        version: str,
        num_trained: int,
        target_model_name: str = None,
    ):
        save_name = f"{path}/{model_name}_{version}_{num_trained}_trained.h5"
        target_model_name = f"target_{model_name}"
        target_save_name = (
            f"{path}/{target_model_name}_{version}_{num_trained}_trained.h5"
        )
        self.model = keras.models.load_model(save_name)
        self.target_model = keras.models.load_model(target_save_name)
    """
