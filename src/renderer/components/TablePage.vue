<template>
  <el-tab-pane :label=header>
    <el-table class="allow-select" ref="table" table-layout='auto' empty-text="没有数据" v-model="data" :data=data
              :highlight-current-row=true border stripe>
      <el-table-column v-for="item in columns" :key="item.prop" :label="item.label" :prop="item.prop"/>
    </el-table>
  </el-tab-pane>
</template>

<script setup lang="ts">
import {ref} from 'vue'
import {ElTabPane, ElTable} from 'element-plus'

interface table_column {
  prop: string
  label: string
}

const columns:table_column[] = [];
const data = ref([{}]);
const header = ref('数据')
</script>

<style scoped>
.allow-select {
  -webkit-user-select: text;
  user-select: text;
}
</style>