import zmq
import pickle
import torch
import torch.nn as nn
import torch.optim as optim
import random
from collections import deque
from env_fuzzy import EnemyCarGame
import matplotlib.pyplot as plt


context = zmq.Context()
socket = context.socket(zmq.REQ)
socket.connect("tcp://localhost:5555")


def send_matrix(matrix):
    # 행렬을 직렬화 (바이너리 데이터로 변환)
    serialized_matrix = pickle.dumps(matrix)

    # 소켓을 통해 직렬화된 데이터 전송
    socket.send(serialized_matrix)

    # 서버로부터 응답 받기
    message = socket.recv()
    print(f"Received reply: {message}")

# DQN 모델 정의
class DQN(nn.Module):
    def __init__(self, input_size, output_size):
        super(DQN, self).__init__()
        self.fc = nn.Sequential(
            nn.Linear(input_size, 128),
            nn.ReLU(),
            nn.Linear(128, 128),
            nn.ReLU(),
            nn.Linear(128, output_size)
        )

    def forward(self, x):
        return self.fc(x)


class DQNAgent:
    def __init__(self, input_size, output_size, gamma=0.99, epsilon=1.0, epsilon_decay=0.995, min_epsilon=0.01):
        self.input_size = input_size
        self.output_size = output_size
        self.gamma = gamma
        self.epsilon = epsilon
        self.epsilon_decay = epsilon_decay
        self.min_epsilon = min_epsilon
        self.policy_net = DQN(input_size, output_size)
        self.target_net = DQN(input_size, output_size)
        self.target_net.load_state_dict(self.policy_net.state_dict())
        self.target_net.eval()
        self.optimizer = optim.Adam(self.policy_net.parameters(), lr=0.001)
        self.memory = deque(maxlen=1000)

    def select_action(self, state):
        if random.random() < self.epsilon:
            return random.choice(range(self.output_size))
        else:
            with torch.no_grad():
                q_values = self.policy_net(torch.tensor(state, dtype=torch.float32))
                return torch.argmax(q_values).item()

    def train(self, batch_size=32):
        if len(self.memory) < batch_size:
            return

        batch = random.sample(self.memory, batch_size)
        states, actions, rewards, next_states, dones = zip(*batch)

        states = torch.tensor(states, dtype=torch.float32)
        actions = torch.tensor(actions, dtype=torch.int64)
        rewards = torch.tensor(rewards, dtype=torch.float32)
        next_states = torch.tensor(next_states, dtype=torch.float32)
        dones = torch.tensor(dones, dtype=torch.float32)

        q_values = self.policy_net(states).gather(1, actions.unsqueeze(1))
        next_q_values = self.target_net(next_states).max(1)[0].detach()
        expected_q_values = rewards.unsqueeze(1) + self.gamma * next_q_values * (1 - dones.unsqueeze(1))

        loss = nn.functional.smooth_l1_loss(q_values, expected_q_values)

        self.optimizer.zero_grad()
        loss.backward()
        self.optimizer.step()

        self.epsilon = max(self.epsilon * self.epsilon_decay, self.min_epsilon)

    def update_target_network(self):
        self.target_net.load_state_dict(self.policy_net.state_dict())


# 환경과 에이전트 초기화
env = EnemyCarGame()
agent = DQNAgent(input_size=env.grid_size[0] * env.grid_size[1], output_size=env.action_space)
print(env.reset())
# 학습 파라미터 설정
num_episodes = 260
max_steps = 300
batch_size = 32
episode_rewards = []

# 학습 진행
for episode in range(num_episodes):
    state = env.reset()
    episode_reward = 0

    for step in range(max_steps):
        action = agent.select_action(state.flatten())
        next_state, reward, done = env.step(action)
        agent.memory.append((state.flatten(), action, reward, next_state.flatten(), done))
        if action == 1:
            episode_reward += 0.1
        episode_reward += reward

        send_matrix(state)
        state = next_state

        if done:
            break

    agent.train(batch_size)
    agent.update_target_network()

    episode_rewards.append(episode_reward)

    if (episode + 1) % 10 == 0:
        print(f"Episode {episode + 1}, Reward: {episode_reward}")

    agent.train(batch_size)
    agent.update_target_network()

    print(f"Episode {episode + 1}, Reward: {episode_reward}")

# 학습된 에이전트를 이용하여 게임 실행
state = env.reset()
while True:
    action = agent.select_action(state.flatten())
    next_state, reward, done = env.step(action)
    state = next_state

    # env.render()  # 게임 화면 출력 (render 함수는 환경에 따라 구현이 필요합니다.)

    if done:
        print("Game Over")
        break


plt.figure(figsize=(10, 6))
plt.plot(range(1, num_episodes + 1), episode_rewards, linestyle='-', color='b')
plt.xlabel('Episode')
plt.ylabel('Reward')
plt.title('Episode Rewards')
plt.grid(True)
plt.show()