<script setup lang="ts">
import {ElTabPane, ElDivider} from 'element-plus'

function open_url(url: string) {
  window.electronAPI.open_url(url);
}
</script>

<template>
    <h1>感谢您的选择</h1>
    <el-divider/>
    <h1>点击 + 连接到您的数据库</h1>
    <h3>Power by</h3>
    <h3>
      <img class="icon" alt="" src="/electron.png"
           @click="open_url('https://www.electronjs.org/')">
      <img class="icon" alt="" src="/vuejs.png"
           @click="open_url('https://vuejs.org/')"/>
      <img class="icon" alt="" src="/sese.png"
           @click="open_url('https://github.com/libsese/sese-core')"/>
      <img class="icon" alt="" src="/element-plus.png"
           @click="open_url('https://element-plus.org/')">
    </h3>
</template>

<style scoped>
.icon {
  margin: 5px;
  width: 50px;
  height: 50px;
  -webkit-user-select: none;
  -webkit-user-drag: none;
  user-select: none;
}
</style>