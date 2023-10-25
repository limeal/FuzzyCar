import math
import random
import matplotlib
import matplotlib.pyplot as plt
from collections import namedtuple, deque
from itertools import count

import torch
import torch.nn as nn
import torch.optim as optim
import torch.nn.functional as F

is_ipython = 'inline' in matplotlib.get_backend()
if is_ipython:
    from IPython import display

plt.ion()

"""
# GPU 사용 경우
device = torch.device("cuda" if torch.cuda.is_avilable() else "cpu")
"""

Transition = namedtuple('Transition', ('state', 'action', 'next_state', 'reward'))


class Environment: ## 미완성.
    def __init__(self):
        # 상태 공간의 차원 수
        self.observation_space = torch.tensor([[0, 0]], dtype=torch.float32)
        # 행동 공간의 차원 수
        self.action_space = 3
        # 초기 상태 설정 (예시로 [0, 0, 0, 0] 으로 초기화)
        self.state = torch.tensor([[0, 0]], dtype=torch.float32)
        # 최대 에피소드 길이 설정 (예시로 100 단계로 설정)
        self.max_steps = 100
        # 현재 단계 초기화
        self.current_step = 0

    def reset(self):
        # 환경 초기화: 상태를 초기화 하고 첫 번째 관찰 반환
        self.state = torch.tensor([[0, 0]], dtype=torch.float32)
        self.current_step = 0
        return self.state

    def step(self, action):
        # action (0, 1, 2)을 취해야 함. 0.25초
        if action == 0:
            self.state = action을 취해서 이동한 reward 값  # 임의의 상태로 이동
        reward = torch.sum(self.state)  # 보상은 상태의 합
        self.current_step += 1
        done = self.current_step >= self.max_steps  # 최대 단계에 도달하면 종료
        info = {}  # 추가 정보는 빈 딕셔너리로 반환
        return self.state, reward, done, info


env = Environment()

class ReplayMemory(object):
    def __init__(self, capacity):
        self.memory = deque([], maxlen=capacity)

    def push(self, *args):
        self.memory.append(Transition(*args))  # transition 저장

    def sample(self, batch_size):
        return random.sample(self.memory, batch_size)

    def __len__(self):
        return len(self.memory)


class DQN(nn.Module):

    def __int__(self, n_observations, n_actions):
        super(DQN, self).__init__()
        self.layer1 = nn.Linear(n_observations, 128)
        self.layer2 = nn.Linear(128, 128)
        self.layer3 = nn.Linear(128, n_actions)

    def forward(self, x):
        x = F.relu(self.layer1(x))
        x = F.relu(self.layer2(x))
        return self.layer3(x)


BATCH_SIZE = 128
GAMMA = 0.99
EPS_START = 0.9
EPS_END = 0.05
EPS_DECAY = 1000
TAU = 0.005
LR = 1e-4

n_actions = env.action_space

state, info = env.reset()
n_observations = len(state)

policy_net = DQN(n_observations, n_actions)  # .to(device) gpu 쓸거면 뒤에다 붙이기
target_net = DQN(n_observations, n_actions)  # .to(device)
target_net.load_state_dict(policy_net.state_dict())

optimizer = optim.AdamW(policy_net.parameters(), lr=LR, amsgrad=True)
memory = ReplayMemory(10000)

steps_done = 0


def select_action(state):
    global steps_done
    sample = random.random()
    eps_threshold = EPS_END + (EPS_START - EPS_END) * math.exp(-1. * steps_done / EPS_DECAY)
    steps_done += 1
    if sample > eps_threshold:
        with torch.no_grad():
            return policy_net(state).max(1)[1].view(1, 1)
    else:
        return torch.tensor([[random.choice(range(n_actions))]], dtype=torch.long)  # gpu 사용시 device=device 넣기


# 시간의 변화 그래프 그리기 ?
episode_durations = []


def plot_durations(show_result=False):
    plt.figure(1)
    durations_t = torch.tensor(episode_durations, dtype=torch.float)
    if show_result:
        plt.title('Result')
    else:
        plt.clf()
        plt.title('Training...')
    plt.xlabel('Episode')
    plt.ylabel('Duration')
    plt.plot(durations_t.numpy())

    # 100개의 에피소드 평균으로 그리기
    if len(durations_t) >= 100:
        means = durations_t.unfold(0, 100, 1).mean(1).view(-1)
        means = torch.cat((torch.zeros(99), means))
        plt.plot(means.numpy())

    plt.pause(0.001)
    if is_ipython:
        if not show_result:
            display.display(plt.gcf())
            display.clear_output(wait=True)
        else:
            display.display(plt.gcf())


def optimize_model():
    if len(memory) < BATCH_SIZE:
        return
    transitions = memory.sample(BATCH_SIZE)

    batch = Transition(*zip(*transitions))

    non_final_mask = torch.tensor(tuple(map(lambda s: s is not None, batch.next_state)),
                                  dtype=torch.bool)  # gpu 사용시 device=device 넣기
    non_final_next_states = torch.cat([s for s in batch.next_state if s is not None])
    state_batch = torch.cat(batch.state)
    action_batch = torch.cat(batch.action)
    reward_batch = torch.cat(batch.reward)

    state_action_values = policy_net(state_batch).gather(1, action_batch)

    next_state_values = torch.zeros(BATCH_SIZE)  # gpu 사용시 device=device 넣기
    with torch.no_grad():
        next_state_values[non_final_mask] = target_net(non_final_next_states).max(1)[0]

    expected_state_action_values = (next_state_values * GAMMA) + reward_batch

    criterion = nn.SmoothL1Loss()
    loss = criterion(state_action_values, expected_state_action_values.unsqueeze(1))

    optimizer.zero_grad()
    loss.backward()

    torch.nn.utils.clip_grad_value_(policy_net.parameters(), 100)
    optimizer.step()


num_episodes = 300

for i_episode in range(num_episodes):
    state, info = env.reset()
    state = torch.tensor(state, dtype=torch.float32).unsqueeze(0)  # gpu 사용시 device=device 넣기
    for t in count():
        action = select_action(state)  # action 결정
        observation, reward, done, _ = env.step(action.item())
        reward = torch.tensor([reward])  # gpu 사용시 device=device 넣기

        if done:
            next_state = None
        else:
            next_state = torch.tensor(observation, dtype=torch.float32).unsqueeze(0)  # gpu 사용시 device=device 넣기

        memory.push(state, action, next_state, reward)
        state = next_state
        optimize_model()

        target_net_state_dict = target_net.state_dict()
        policy_net_state_dict = policy_net.state_dict()
        for key in policy_net_state_dict:
            target_net_state_dict[key] = policy_net_state_dict[key] * TAU + target_net_state_dict[key] * (1 - TAU)
        target_net.load_state_dict(target_net_state_dict)

        if done:
            episode_durations.append(t + 1)
            plot_durations()
            break

print('Complete')
plot_durations(show_result=True)
plt.ioff()
plt.show()
