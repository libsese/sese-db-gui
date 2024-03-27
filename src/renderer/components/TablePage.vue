<template>
  <el-table class="allow-select" ref="table" table-layout='auto' empty-text="没有数据" v-model="props.data" :data=props.data
            :highlight-current-row=true border stripe>
    <el-table-column v-for="item in columns" :key="item.prop" :label="item.label" :prop="item.prop"/>
  </el-table>
</template>

<script setup lang="ts">
import {ref} from 'vue'
import {ElTable, ElButton} from 'element-plus'

export interface TableColumn {
  prop: string
  label: string
}

const props = defineProps({
  columns: {
    type: Array<TableColumn>,
    default: []
  },
  data: {
    type: ref<Array<any>>,
    default: ref([{}])
  }
})

</script>

<style scoped>
.allow-select {
  -webkit-user-select: text;
  user-select: text;
}
</style>