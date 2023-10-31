import torch
import torch.nn as nn
import torch.optim as optim
import random
from collections import deque
import matplotlib.pyplot as plt
import numpy as np

buffer_limit = 50000
class ReplayBuffer():
    def __init__(self):
        self.buffer = deque(maxlen=buffer_limit)
        
    def put(self, transition):
        self.buffer.append(transition)
        
    def sample(self, n):
        mini_batch = random.sample(self.buffer, n)
        s_lst, a_lst, r_lst, s_prime_lst, done_mask_lst = [], [], [], [], [] 
        # done_mask_lst : 종료 상태의 밸류를 마스킹해주기 위해 만든 변수
        
        for transition in mini_batch:
            s, a, r, s_prime, done_mask = transition
            s_lst.append(s)
            a_lst.append([a])
            r_lst.append([r])
            s_prime_lst.append(s_prime)
            done_mask_lst.append([done_mask])
            
        return torch.tensor(s_lst, dtype=torch.float), torch.tensor(a_lst), torch.tensor(r_lst), \
                torch.tensor(s_prime_lst, dtype=torch.float), torch.tensor(done_mask_lst)
    
    def size(self):
        return len(self.buffer)

# DQN 모델 정의
class DQN(nn.Module):
    def __init__(self, input_size, output_size):
        super(DQN, self).__init__()
        self.fc = nn.Sequential(
            nn.Linear(input_size, 128),
            nn.ReLU(),
            nn.Linear(128, 128),
            nn.ReLU(),
            nn.Linear(128, output_size),
        )

    def forward(self, x):
        return self.fc(x)
    
losses =  []

class DQNAgent:
    def __init__(
        self,
        input_size,
        output_size,
        gamma=0.99,
        epsilon=1.0,
        epsilon_decay=0.995,
        min_epsilon=0.01,
    ):
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
            
    def save(self, path):
        torch.save(self.policy_net.state_dict(), path)
    
    def load(self, path):
        self.policy_net.load_state_dict(torch.load(path))
        self.target_net.load_state_dict(self.policy_net.state_dict())
        self.target_net.eval()

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
        expected_q_values = rewards.unsqueeze(1) + self.gamma * next_q_values * (
            1 - dones.unsqueeze(1)
        )

        loss = nn.functional.smooth_l1_loss(q_values, expected_q_values)

        loss_arr = loss.detach()

        losses.append(loss_arr)
        self.optimizer.zero_grad()
        loss.backward()
        self.optimizer.step()

        self.epsilon = max(self.epsilon * self.epsilon_decay, self.min_epsilon)

    def update_target_network(self):
        self.target_net.load_state_dict(self.policy_net.state_dict())


# 환경과 에이전트 초기화
def train(agent, env, num_episodes=300, max_steps=300, batch_size=32):
    memory = ReplayBuffer()
    # 학습 파라미터 설정
    episode_rewards = []
    
    # 학습 진행
    for episode in range(num_episodes):
        state = env.reset()
        episode_reward = 0

        for step in range(max_steps):
            action = agent.select_action(state.flatten())
            next_state, reward, done = env.step(action)
            agent.memory.append(
                (state.flatten(), action, reward, next_state.flatten(), done)
            )
            memory.put([state,action,reward,next_state,done])

            if not done:
                episode_reward += 0.3

            episode_reward += reward

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
    
    if memory.size() > 2000:
        agent.train(batch_size)
    
    plt.figure(figsize=(10, 6))
    plt.plot(range(1, num_episodes + 1), episode_rewards, linestyle='-', color='b')
    plt.xlabel('Episode')
    plt.ylabel('Reward')
    plt.title('Episode Rewards')
    plt.grid(True)
    plt.show()
    
    return agent
    