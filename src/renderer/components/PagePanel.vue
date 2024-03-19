<script setup lang="ts">
import {ElTabs} from 'element-plus';
import WelcomePage from "./WelcomePage.vue";
</script>

<template>
  <div class="page-panel-box">
    <el-tabs type="border-card" class="page-box" :closable=true>
      <welcome-page/>
      <slot/>
    </el-tabs>
  </div>
</template>

<style scoped>
.page-panel-box {
  width: 100%;
  height: 100%;
}

.page-box {
  width: 100%;
  height: 100%;
}
</style>