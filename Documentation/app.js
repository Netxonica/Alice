'use strict';

(() => {
  const STORAGE_KEY = 'alice-api-reference-v2';
  const LEGACY_STORAGE_KEY = 'alice-api-reference-v1';
  const ENTITY_KINDS = [
    ['macro', 'Macro'], ['function-like-macro', 'Function-like macro'],
    ['template-entity', 'Templated entity'], ['type-alias', 'Type alias'],
    ['concept', 'Concept'], ['class', 'Class'], ['struct', 'Struct'],
    ['union', 'Union'], ['enum', 'Enum'], ['free-function', 'Free function'],
    ['function-template', 'Function template'], ['class-template', 'Class template'],
    ['variable-template', 'Variable template'], ['variable', 'Variable'],
    ['constant', 'Constant'], ['namespace', 'Namespace'], ['other', 'Other declaration']
  ];
  const $ = (selector, root = document) => root.querySelector(selector);
  const $$ = (selector, root = document) => [...root.querySelectorAll(selector)];

  const starterData = {
    schemaVersion: 1,
    project: { name: 'Alice', version: '0.0.1', subtitle: 'C++26 game engine and development platform' },
    categories: [
      {
        id: 'core', name: 'Core', description: 'Foundational language utilities, compiler abstractions, and low-level building blocks.',
        features: [
          {
            id: 'no-unique-address', name: 'NoUniqueAddress',
            summary: 'A portable utility related to the C++ no_unique_address attribute.',
            description: 'This is a starter documentation entry for the NoUniqueAddress feature. Replace the namespace, detailed behaviour, and example with the exact public API exposed by the current Alice header before publishing the reference. The sample code below demonstrates the underlying standard C++ attribute, not an assumed Alice wrapper interface.',
            namespace: { value: 'Fill in from source', description: 'The namespace in which Alice declares the feature. Confirm the exact qualified name in the header.' },
            introduced: { value: '0.0.1', description: 'The Alice release in which this feature was introduced.' },
            standard: { value: 'C++20 — [[no_unique_address]]', description: 'The standard language attribute used by the feature is part of C++20.' },
            sourceUrl: 'https://github.com/Netxonica/Alice/Source/Core/NoUniqueAddress.hpp',
            testUrl: 'https://github.com/Netxonica/Alice/Test/Core/NoUniqueAddress.cpp',
            tags: ['core', 'layout', 'portability', 'C++20'],
            sections: [
              { title: 'Purpose', body: 'Use this section to explain the problem the utility solves, the guarantees it provides, and any implementation-specific behaviour that callers should understand.' },
              { title: 'Portability notes', body: 'Document compiler support, fallback behaviour, ABI considerations, and any restrictions that are important for supported targets.' }
            ],
            examples: [
              {
                title: 'Underlying language feature',
                description: 'A minimal illustration of [[no_unique_address]]. Adapt this example to the actual Alice declaration and include path.',
                code: '#include <cstdint>\n\nstruct Empty {};\n\nstruct CompactValue {\n    [[no_unique_address]] Empty marker;\n    std::uint32_t value;\n};'
              }
            ]
          }
        ]
      },
      { id: 'memory', name: 'Memory', description: 'Ownership, allocation, lifetime, and memory-management facilities.', features: [] },
      { id: 'diagnostics', name: 'Diagnostics', description: 'Assertions, diagnostic reporting, source locations, and debugging utilities.', features: [] },
      { id: 'utilities', name: 'Utilities', description: 'General-purpose types and helpers used throughout the engine.', features: [] }
    ]
  };

  let data = loadData();
  let activeCategoryId = data.categories[0]?.id ?? null;
  let activeFeatureId = data.categories[0]?.features[0]?.id ?? null;
  let expandedCategories = new Set(data.categories.map(category => category.id));

  const sidebar = $('#sidebar');
  const sidebarScrim = $('#sidebarScrim');
  const categoryNav = $('#categoryNav');
  const docSearch = $('#docSearch');
  const view = $('#documentationView');
  const categoryDialog = $('#categoryDialog');
  const featureDialog = $('#featureDialog');
  const categoryForm = $('#categoryForm');
  const featureForm = $('#featureForm');
  const sectionsEditor = $('#sectionsEditor');
  const examplesEditor = $('#examplesEditor');
  const templateParametersEditor = $('#templateParametersEditor');
  const parametersEditor = $('#parametersEditor');
  const membersEditor = $('#membersEditor');
  const importFile = $('#importFile');

  function loadData() {
    try {
      const stored = localStorage.getItem(STORAGE_KEY) || localStorage.getItem(LEGACY_STORAGE_KEY);
      if (stored) {
        const parsed = JSON.parse(stored);
        if (isValidDocument(parsed)) return normalizeDocument(parsed);
      }
    } catch (error) {
      console.warn('Could not load the saved Alice documentation workspace:', error);
    }
    return structuredCloneSafe(starterData);
  }

  function structuredCloneSafe(value) {
    return JSON.parse(JSON.stringify(value));
  }

  function isValidDocument(candidate) {
    return Boolean(candidate && typeof candidate === 'object' && Array.isArray(candidate.categories)
      && candidate.categories.every(category => category && typeof category.id === 'string'
        && typeof category.name === 'string' && Array.isArray(category.features)));
  }

  function normalizeDocument(candidate) {
    const normalized = {
      schemaVersion: 2,
      project: {
        name: String(candidate.project?.name || 'Alice'),
        version: String(candidate.project?.version || '0.0.1'),
        subtitle: String(candidate.project?.subtitle || 'C++26 game engine and development platform')
      },
      categories: candidate.categories.map((category, categoryIndex) => ({
        id: String(category.id || `category-${categoryIndex + 1}`),
        name: String(category.name || `Category ${categoryIndex + 1}`),
        description: String(category.description || ''),
        features: category.features.map((feature, featureIndex) => normalizeFeature(feature, categoryIndex, featureIndex))
      }))
    };
    return normalized;
  }

  function normalizeFeature(feature, categoryIndex = 0, featureIndex = 0) {
    const meta = key => ({
      value: String(feature?.[key]?.value ?? ''),
      description: String(feature?.[key]?.description ?? '')
    });
    return {
      id: String(feature?.id || `feature-${categoryIndex + 1}-${featureIndex + 1}`),
      name: String(feature?.name || 'Untitled feature'),
      summary: String(feature?.summary || ''),
      description: String(feature?.description || ''),
      namespace: meta('namespace'),
      introduced: meta('introduced'),
      standard: meta('standard'),
      sourceUrl: String(feature?.sourceUrl || ''),
      testUrl: String(feature?.testUrl || ''),
      entityKind: ENTITY_KINDS.some(([key]) => key === feature?.entityKind) ? feature.entityKind : 'other',
      scopedEnum: Boolean(feature?.scopedEnum),
      aliasedType: String(feature?.aliasedType || ''),
      aliasedTypeRef: String(feature?.aliasedTypeRef || ''),
      returnType: String(feature?.returnType || ''),
      returnTypeRef: String(feature?.returnTypeRef || ''),
      templateParameters: Array.isArray(feature?.templateParameters) ? feature.templateParameters.map(normalizeTemplateParameter) : [],
      parameters: Array.isArray(feature?.parameters) ? feature.parameters.map(normalizeParameter) : [],
      members: Array.isArray(feature?.members) ? feature.members.map(normalizeMember) : [],
      tags: Array.isArray(feature?.tags) ? feature.tags.map(String) : [],
      sections: Array.isArray(feature?.sections) ? feature.sections.map(section => ({ title: String(section?.title || ''), body: String(section?.body || '') })) : [],
      examples: Array.isArray(feature?.examples) ? feature.examples.map(example => ({ title: String(example?.title || 'Example'), description: String(example?.description || ''), code: String(example?.code || '') })) : []
    };
  }

  function normalizeParameter(parameter = {}) {
    return {
      id: String(parameter.id || makeId('parameter')),
      name: String(parameter.name || ''),
      type: String(parameter.type || ''),
      typeRef: String(parameter.typeRef || ''),
      defaultValue: String(parameter.defaultValue || ''),
      description: String(parameter.description || '')
    };
  }

  function normalizeTemplateParameter(parameter = {}) {
    return {
      id: String(parameter.id || makeId('template-parameter')),
      name: String(parameter.name || ''),
      kind: ['type', 'non-type', 'template'].includes(parameter.kind) ? parameter.kind : 'type',
      type: String(parameter.type || ''),
      typeRef: String(parameter.typeRef || ''),
      defaultValue: String(parameter.defaultValue || ''),
      description: String(parameter.description || '')
    };
  }

  function normalizeMember(member = {}) {
    return {
      id: String(member.id || makeId('member')),
      kind: String(member.kind || 'data-member'),
      name: String(member.name || ''),
      type: String(member.type || ''),
      typeRef: String(member.typeRef || ''),
      entityRef: String(member.entityRef || ''),
      value: String(member.value || ''),
      access: ['public', 'protected', 'private'].includes(member.access) ? member.access : 'public',
      isStatic: Boolean(member.isStatic),
      returnType: String(member.returnType || ''),
      returnTypeRef: String(member.returnTypeRef || ''),
      description: String(member.description || ''),
      parameters: Array.isArray(member.parameters) ? member.parameters.map(normalizeParameter) : [],
      templateParameters: Array.isArray(member.templateParameters) ? member.templateParameters.map(normalizeTemplateParameter) : []
    };
  }

  function persist() {
    try {
      localStorage.setItem(STORAGE_KEY, JSON.stringify(data));
    } catch (error) {
      console.warn('Could not save the Alice documentation workspace:', error);
      showToast('The browser could not save this change. Export your data to keep a backup.', true);
    }
  }

  function escapeHTML(value) {
    return String(value ?? '').replace(/[&<>"']/g, character => ({
      '&': '&amp;', '<': '&lt;', '>': '&gt;', '"': '&quot;', "'": '&#39;'
    })[character]);
  }

  function safeURL(value) {
    if (!value) return '';
    try {
      const url = new URL(value);
      return ['http:', 'https:'].includes(url.protocol) ? url.href : '';
    } catch {
      return '';
    }
  }

  function makeId(prefix) {
    if (window.crypto?.randomUUID) return `${prefix}-${crypto.randomUUID()}`;
    return `${prefix}-${Date.now().toString(36)}-${Math.random().toString(36).slice(2, 8)}`;
  }

  function slugify(value) {
    return String(value).toLowerCase().normalize('NFD').replace(/[\u0300-\u036f]/g, '')
      .replace(/[^a-z0-9]+/g, '-').replace(/^-|-$/g, '') || 'item';
  }

  function allFeatures() {
    return data.categories.flatMap(category => category.features.map(feature => ({ category, feature })));
  }

  function findFeature(featureId) {
    for (const category of data.categories) {
      const feature = category.features.find(item => item.id === featureId);
      if (feature) return { category, feature };
    }
    return null;
  }

  function entityKindLabel(kind) {
    return ENTITY_KINDS.find(([key]) => key === kind)?.[1] || 'Other declaration';
  }

  function entityKindGlyph(kind) {
    return ({
      macro: '#', 'function-like-macro': '#ƒ', 'template-entity': 'T',
      'type-alias': '≡', concept: '◇', class: 'C', struct: 'S', union: 'U',
      enum: 'E', 'free-function': 'ƒ', 'function-template': 'ƒT',
      'class-template': 'CT', 'variable-template': 'VT', variable: 'x',
      constant: 'π', namespace: '⌘', other: '·'
    })[kind] || '·';
  }

  function entityKindOptions(selected = 'other') {
    return ENTITY_KINDS.map(([key, label]) => `<option value="${key}"${key === selected ? ' selected' : ''}>${label}</option>`).join('');
  }

  function typeEntityOptions(selected = '') {
    const typeKinds = new Set(['class', 'struct', 'union', 'enum', 'type-alias', 'concept', 'class-template', 'template-entity']);
    const options = allFeatures().filter(({ feature }) => typeKinds.has(feature.entityKind));
    return `<option value="">— No linked API type —</option>${options.map(({ category, feature }) => `
      <option value="${escapeHTML(feature.id)}"${feature.id === selected ? ' selected' : ''}>${escapeHTML(feature.name)} · ${escapeHTML(category.name)}</option>`).join('')}`;
  }

  function referenceMarkup(type, referenceId, fallback = '') {
    const target = referenceId ? findFeature(referenceId) : null;
    const label = String(type || target?.feature.name || fallback || 'Unspecified type').trim();
    if (!target) return `<code class="declaration-type">${escapeHTML(label)}</code>`;
    return `<button type="button" class="inline-type-link" data-action="open-reference" data-feature-id="${escapeHTML(target.feature.id)}" title="Open ${escapeHTML(target.feature.name)} documentation"><code>${escapeHTML(label)}</code><span aria-hidden="true">↗</span></button>`;
  }

  function declarationKindLabel(kind) {
    const labels = {
      'data-member': 'Data member', 'member-function': 'Member function',
      'static-data-member': 'Static data member', 'static-member-function': 'Static member function',
      'member-function-template': 'Member function template', 'static-member-function-template': 'Static member function template',
      'nested-type': 'Nested type', 'type-alias': 'Type alias', 'nested-class': 'Nested class',
      'nested-struct': 'Nested struct', 'nested-union': 'Nested union', 'nested-enum': 'Nested enum',
      enumerator: 'Enumerator', 'friend-function': 'Friend function', 'other': 'Other member'
    };
    return labels[kind] || 'Declaration';
  }

  function isFunctionEntity(feature) {
    return ['free-function', 'function-template', 'function-like-macro'].includes(feature.entityKind)
      || Boolean(feature.parameters?.length) || Boolean(feature.returnType) || Boolean(feature.returnTypeRef);
  }

  function isAggregateEntity(feature) {
    return ['class', 'struct', 'union', 'enum'].includes(feature.entityKind);
  }

  function currentCategory() {
    return data.categories.find(category => category.id === activeCategoryId) || null;
  }

  function currentFeature() {
    return activeFeatureId ? findFeature(activeFeatureId) : null;
  }

  function setCurrentCategory(categoryId) {
    activeCategoryId = categoryId;
    activeFeatureId = null;
    expandedCategories.add(categoryId);
    render();
  }

  function openFeature(categoryId, featureId) {
    activeCategoryId = categoryId;
    activeFeatureId = featureId;
    expandedCategories.add(categoryId);
    render();
    closeSidebar();
    window.scrollTo({ top: 0, behavior: 'smooth' });
  }

  function showToast(message, isError = false) {
    const toast = document.createElement('div');
    toast.className = `toast${isError ? ' error' : ''}`;
    toast.textContent = message;
    $('#toastRegion').append(toast);
    window.setTimeout(() => toast.remove(), 3400);
  }

  function featureTotal() {
    return data.categories.reduce((total, category) => total + category.features.length, 0);
  }

  function render() {
    $('#sidebarVersion').textContent = `v${data.project.version}`;
    $('#featureCount').textContent = String(featureTotal()).padStart(2, '0');
    renderSidebar();
    renderMainView();
  }

  function renderSidebar() {
    const query = docSearch.value.trim().toLowerCase();
    const categories = data.categories.map(category => {
      const categoryMatches = category.name.toLowerCase().includes(query)
        || category.description.toLowerCase().includes(query);
      const matches = query && !categoryMatches
        ? category.features.filter(feature => [feature.name, feature.summary, feature.description, entityKindLabel(feature.entityKind), ...(feature.tags || []), ...(feature.members || []).map(member => `${member.name} ${member.type} ${member.description}`)].join(' ').toLowerCase().includes(query))
        : category.features;
      return { category, matches, visible: !query || categoryMatches || matches.length > 0 };
    }).filter(item => item.visible);

    if (!categories.length) {
      categoryNav.innerHTML = '<div class="nav-empty">No matching categories or features.</div>';
      return;
    }

    categoryNav.innerHTML = categories.map(({ category, matches }) => {
      const isExpanded = query.length > 0 || expandedCategories.has(category.id);
      const categoryActive = activeCategoryId === category.id && !activeFeatureId;
      const glyph = escapeHTML((category.name.trim()[0] || '•').toUpperCase());
      const featuresHTML = matches.length
        ? matches.map(feature => `
          <button class="feature-nav-link${activeFeatureId === feature.id ? ' active' : ''}" type="button"
            data-action="open-feature" data-category-id="${escapeHTML(category.id)}" data-feature-id="${escapeHTML(feature.id)}"
            ${activeFeatureId === feature.id ? 'aria-current="page"' : ''}>
            <span class="nav-file-icon">${escapeHTML(entityKindGlyph(feature.entityKind))}</span><span class="feature-nav-text"><span class="feature-nav-name">${escapeHTML(feature.name)}</span><span class="feature-nav-kind">${escapeHTML(entityKindLabel(feature.entityKind))}</span></span>
          </button>`).join('')
        : '<div class="nav-empty">No features yet.</div>';
      return `
        <div class="category-group${isExpanded ? '' : ' collapsed'}" data-category-group="${escapeHTML(category.id)}">
          <div class="category-head">
            <button class="category-select${categoryActive ? ' active' : ''}" type="button" data-action="open-category" data-category-id="${escapeHTML(category.id)}" ${categoryActive ? 'aria-current="page"' : ''}>
              <span class="category-glyph">${glyph}</span><span class="category-name">${escapeHTML(category.name)}</span><span class="category-size">${String(category.features.length).padStart(2, '0')}</span>
            </button>
            <button class="category-toggle" type="button" aria-label="${isExpanded ? 'Collapse' : 'Expand'} ${escapeHTML(category.name)}" aria-expanded="${isExpanded}" data-action="toggle-category" data-category-id="${escapeHTML(category.id)}">
              <svg viewBox="0 0 24 24" aria-hidden="true"><path d="m7 10 5 5 5-5"></path></svg>
            </button>
          </div>
          <div class="feature-nav-list">${featuresHTML}</div>
        </div>`;
    }).join('');
  }

  function renderMainView() {
    const selected = currentFeature();
    if (selected) {
      $('#breadcrumbCurrent').textContent = `${selected.category.name} / ${selected.feature.name}`;
      view.innerHTML = renderFeaturePage(selected.category, selected.feature);
      return;
    }
    const category = currentCategory();
    if (category) {
      $('#breadcrumbCurrent').textContent = category.name;
      view.innerHTML = renderCategoryPage(category);
      return;
    }
    $('#breadcrumbCurrent').textContent = 'Overview';
    view.innerHTML = renderHomePage();
  }

  function renderHomePage() {
    const categories = data.categories;
    const features = allFeatures();
    const cards = categories.map(category => `
      <button class="category-card" type="button" data-action="open-category" data-category-id="${escapeHTML(category.id)}">
        <span class="card-topline"><span class="card-symbol">${escapeHTML((category.name[0] || '•').toUpperCase())}</span><span class="card-count">${category.features.length} ${category.features.length === 1 ? 'FEATURE' : 'FEATURES'}</span></span>
        <h3>${escapeHTML(category.name)}</h3><p>${escapeHTML(category.description || 'No category description has been added.')}</p><span class="card-arrow" aria-hidden="true">↗</span>
      </button>`).join('');
    const recent = features.slice(0, 5).map(({ category, feature }) => featureListCard(category, feature)).join('');
    return `
      <section class="hero">
        <span class="hero-kicker">NETXONICA / ENGINE DOCUMENTATION</span>
        <h1>Alice API<br>Reference.</h1>
        <p>A structured reference for Alice’s public C++ interface. Browse features by category, inspect their requirements, and explore practical usage examples.</p>
        <div class="hero-meta"><span class="hero-pill">ALICE v${escapeHTML(data.project.version)}</span><span class="hero-pill">C++26</span><span class="hero-pill">${features.length} DOCUMENTED ${features.length === 1 ? 'FEATURE' : 'FEATURES'}</span></div>
      </section>
      <div class="section-heading-row"><div><h2>Browse by category</h2><p>Explore the API by subsystem.</p></div><span class="subtle-count">${String(categories.length).padStart(2, '0')} CATEGORIES</span></div>
      ${categories.length ? `<div class="category-card-grid">${cards}</div>` : emptyState('No categories yet', 'Create a category to start organising the Alice API.', 'add-category')}
      <div class="section-heading-row"><div><h2>Feature index</h2><p>Direct access to documented API entries.</p></div><span class="subtle-count">${String(features.length).padStart(2, '0')} ENTRIES</span></div>
      ${recent ? `<div class="feature-list">${recent}</div>` : emptyState('No features documented', 'Add your first feature to begin building the reference.', 'add-feature')}`;
  }

  function renderCategoryPage(category) {
    const featureCards = category.features.map(feature => featureListCard(category, feature)).join('');
    return `
      <div class="page-header">
        <div class="page-header-copy"><span class="hero-kicker">API CATEGORY</span><h1>${escapeHTML(category.name)}</h1><p class="page-summary">${escapeHTML(category.description || 'No description has been added for this category yet.')}</p></div>
        <div class="page-actions"><button class="button button-primary" type="button" data-action="add-feature-in-category" data-category-id="${escapeHTML(category.id)}"><span>+</span> Add feature</button></div>
      </div>
      <div class="section-heading-row"><div><h2>Features</h2><p>API entries in ${escapeHTML(category.name)}.</p></div><span class="subtle-count">${String(category.features.length).padStart(2, '0')} ENTRIES</span></div>
      ${featureCards ? `<div class="feature-list">${featureCards}</div>` : emptyState('This category is empty', 'Add an API feature to make it available in the navigation sidebar.', 'add-feature-in-category', category.id)}`;
  }

  function featureListCard(category, feature) {
    return `<button class="feature-list-card" type="button" data-action="open-feature" data-category-id="${escapeHTML(category.id)}" data-feature-id="${escapeHTML(feature.id)}">
      <span class="feature-list-icon">${escapeHTML(entityKindGlyph(feature.entityKind))}</span><span class="feature-list-content"><strong>${escapeHTML(feature.name)}</strong><span>${escapeHTML(feature.summary || 'No short summary has been added.')}</span><small class="entity-kind-pill">${escapeHTML(entityKindLabel(feature.entityKind))}</small></span><span class="feature-list-arrow" aria-hidden="true">↗</span>
    </button>`;
  }

  function emptyState(title, description, action, categoryId = '') {
    const buttonLabel = action === 'add-category' ? 'Create category' : 'Add feature';
    const dataCategory = categoryId ? ` data-category-id="${escapeHTML(categoryId)}"` : '';
    return `<div class="empty-state"><span class="empty-state-mark" aria-hidden="true">+</span><h2>${escapeHTML(title)}</h2><p>${escapeHTML(description)}</p><button class="button button-primary" type="button" data-action="${action}"${dataCategory}>${buttonLabel}</button></div>`;
  }

  function metadataCard(label, icon, metadata) {
    const value = metadata?.value?.trim() || 'Not specified';
    const description = metadata?.description?.trim() || 'No description has been provided for this field.';
    return `<div class="metadata-card"><div class="metadata-card-head"><span class="metadata-icon">${icon}</span>${escapeHTML(label)}</div><span class="metadata-value">${escapeHTML(value)}</span><p class="metadata-description">${escapeHTML(description)}</p></div>`;
  }

  function renderTemplateParameters(parameters, heading = 'Template parameters') {
    if (!parameters?.length) return '';
    const rows = parameters.map(parameter => `
      <tr>
        <td><span class="parameter-kind">${escapeHTML(parameter.kind || 'type')}</span></td>
        <td><code class="declaration-name">${escapeHTML(parameter.name || 'Unnamed')}</code></td>
        <td>${parameter.type || parameter.typeRef ? referenceMarkup(parameter.type, parameter.typeRef) : '<span class="muted-value">—</span>'}</td>
        <td>${parameter.defaultValue ? `<code class="declaration-default">${escapeHTML(parameter.defaultValue)}</code>` : '<span class="muted-value">—</span>'}</td>
        <td>${escapeHTML(parameter.description || '—')}</td>
      </tr>`).join('');
    return `<section class="content-section parameter-section"><h2><span class="section-index">T</span> ${escapeHTML(heading)}</h2><div class="declaration-table-wrap"><table class="declaration-table"><thead><tr><th>Kind</th><th>Name</th><th>Type</th><th>Default</th><th>Description</th></tr></thead><tbody>${rows}</tbody></table></div></section>`;
  }

  function renderFunctionParameters(parameters, returnType, returnTypeRef, forceShow = false) {
    if (!parameters?.length && !returnType && !returnTypeRef && !forceShow) return '';
    const rows = (parameters || []).map(parameter => `
      <tr>
        <td>${referenceMarkup(parameter.type, parameter.typeRef)}</td>
        <td><code class="declaration-name">${escapeHTML(parameter.name || 'Unnamed')}</code></td>
        <td>${parameter.defaultValue ? `<code class="declaration-default">${escapeHTML(parameter.defaultValue)}</code>` : '<span class="muted-value">—</span>'}</td>
        <td>${escapeHTML(parameter.description || '—')}</td>
      </tr>`).join('');
    const returnMarkup = returnType || returnTypeRef
      ? `<div class="return-type-row"><span class="return-type-label">RETURNS</span>${referenceMarkup(returnType, returnTypeRef)}</div>` : '';
    return `<section class="content-section parameter-section"><h2><span class="section-index">P</span> Function parameters</h2>${returnMarkup}${parameters?.length ? `<div class="declaration-table-wrap"><table class="declaration-table"><thead><tr><th>Type</th><th>Name</th><th>Default</th><th>Description</th></tr></thead><tbody>${rows}</tbody></table></div>` : '<p class="section-note">No parameters.</p>'}</section>`;
  }

  function renderMember(member, index) {
    const isEnumerator = member.kind === 'enumerator';
    const isFunction = ['member-function', 'static-member-function', 'friend-function', 'member-function-template', 'static-member-function-template'].includes(member.kind);
    const linkedEntity = member.entityRef ? findFeature(member.entityRef) : null;
    const nameMarkup = linkedEntity
      ? `<button type="button" class="inline-type-link declaration-member-link" data-action="open-reference" data-feature-id="${escapeHTML(linkedEntity.feature.id)}"><code>${escapeHTML(member.name || linkedEntity.feature.name)}</code><span aria-hidden="true">↗</span></button>`
      : `<code class="declaration-name">${escapeHTML(member.name || `unnamed_${index + 1}`)}</code>`;
    const signatureType = isFunction ? member.returnType : member.type;
    const typeMarkup = isFunction
      ? referenceMarkup(signatureType, member.returnTypeRef, 'void')
      : (member.type || member.typeRef ? referenceMarkup(member.type, member.typeRef) : '');
    const access = isEnumerator ? '' : `<span class="access-pill access-${escapeHTML(member.access || 'public')}">${escapeHTML(member.access || 'public')}</span>`;
    const staticFlag = member.isStatic || member.kind === 'static-data-member' || member.kind === 'static-member-function' || member.kind === 'static-member-function-template'
      ? '<span class="member-qualifier">static</span>' : '';
    const signature = isFunction
      ? `<div class="member-signature">${typeMarkup}<span class="signature-space"> </span>${nameMarkup}<span class="signature-punctuation">(</span>${(member.parameters || []).map((parameter, parameterIndex) => `${parameterIndex ? '<span class="signature-punctuation">, </span>' : ''}${referenceMarkup(parameter.type, parameter.typeRef)} <code class="declaration-name">${escapeHTML(parameter.name || `arg${parameterIndex}`)}</code>`).join('')}<span class="signature-punctuation">)</span></div>`
      : isEnumerator
        ? `<div class="member-signature">${nameMarkup}${member.value ? `<span class="signature-punctuation"> = </span><code class="declaration-default">${escapeHTML(member.value)}</code>` : ''}</div>`
        : `<div class="member-signature">${typeMarkup ? `${typeMarkup}<span class="signature-space"> </span>` : ''}${nameMarkup}${member.value ? `<span class="signature-punctuation"> = </span><code class="declaration-default">${escapeHTML(member.value)}</code>` : ''}</div>`;
    const nestedTemplates = member.templateParameters?.length
      ? `<div class="member-parameter-list"><span>Template parameters</span>${member.templateParameters.map(parameter => `<span><code>${escapeHTML(parameter.name)}</code>${parameter.type || parameter.typeRef ? `: ${referenceMarkup(parameter.type, parameter.typeRef)}` : ''}${parameter.description ? `<small>${escapeHTML(parameter.description)}</small>` : ''}</span>`).join('')}</div>` : '';
    const nestedParameters = isFunction && member.parameters?.length
      ? `<div class="member-parameter-list"><span>Parameters</span>${member.parameters.map(parameter => `<span>${referenceMarkup(parameter.type, parameter.typeRef)} <code>${escapeHTML(parameter.name)}</code>${parameter.description ? `<small>${escapeHTML(parameter.description)}</small>` : ''}</span>`).join('')}</div>` : '';
    const description = member.description ? `<p class="member-description">${escapeHTML(member.description)}</p>` : '';
    const entityAction = linkedEntity ? `<button type="button" class="member-open-link" data-action="open-reference" data-feature-id="${escapeHTML(linkedEntity.feature.id)}">Open declaration ↗</button>` : '';
    return `<article class="declaration-member${isEnumerator ? ' enumerator-member' : ''}">
      <div class="declaration-member-top"><span class="member-kind-label">${escapeHTML(declarationKindLabel(member.kind))}</span><span class="member-badges">${access}${staticFlag}</span></div>
      ${signature}${description}${nestedTemplates}${nestedParameters}${entityAction}
    </article>`;
  }

  function renderAggregateContents(feature) {
    if (!isAggregateEntity(feature) && !['class-template', 'template-entity'].includes(feature.entityKind) && !feature.members?.length) return '';
    const members = feature.members || [];
    const isEnum = feature.entityKind === 'enum';
    const contentsTitle = isEnum ? 'Enumerators' : 'Members';
    const rows = members.map(renderMember).join('');
    const stats = `${members.length} ${members.length === 1 ? (isEnum ? 'enumerator' : 'member') : (isEnum ? 'enumerators' : 'members')}`;
    return `<section class="content-section aggregate-section" id="contents"><div class="section-title-with-count"><h2><span class="section-index">04</span> ${contentsTitle}</h2><span class="subtle-count">${escapeHTML(stats)}</span></div>
      ${feature.scopedEnum && isEnum ? '<p class="section-note">Scoped enumeration (<code>enum class</code>).</p>' : ''}
      ${rows ? `<div class="declaration-members">${rows}</div>` : `<div class="empty-members"><strong>No ${isEnum ? 'enumerators' : 'members'} documented.</strong><span>Add the declarations exposed by this ${escapeHTML(feature.entityKind)}.</span></div>`}
    </section>`;
  }

  function renderFeaturePage(category, feature) {
    const tags = (feature.tags || []).filter(Boolean).map(tag => `<span class="tag">${escapeHTML(tag)}</span>`).join('');
    const sections = (feature.sections || []).map((section, index) => `
      <article class="detail-section" id="detail-section-${index}"><h3>${escapeHTML(section.title || `Details ${index + 1}`)}</h3><p>${escapeHTML(section.body || 'No description has been provided.')}</p></article>`).join('');
    const examples = (feature.examples || []).map((example, index) => `
      <article class="example-card">
        <div class="example-heading"><div><h3>${escapeHTML(example.title || `Example ${index + 1}`)}</h3>${example.description ? `<p>${escapeHTML(example.description)}</p>` : ''}</div><span class="code-language">C++</span><button class="copy-button" type="button" data-action="copy-example" data-example-index="${index}"><svg viewBox="0 0 24 24" aria-hidden="true"><rect x="8" y="8" width="12" height="12" rx="2"></rect><path d="M16 8V5a2 2 0 0 0-2-2H5a2 2 0 0 0-2 2v9a2 2 0 0 0 2 2h3"></path></svg> Copy</button></div>
        <div class="code-scroll"><pre><code>${highlightCpp(example.code || '')}</code></pre></div>
      </article>`).join('');
    const source = safeURL(feature.sourceUrl);
    const tests = safeURL(feature.testUrl);
    const sourceSection = source || tests ? `
      <section class="content-section" id="sources"><h2><span class="section-index">07</span> Source &amp; tests</h2><div class="source-links">${source ? `<a class="source-link" href="${escapeHTML(source)}" target="_blank" rel="noreferrer">Source header <span>↗</span></a>` : ''}${tests ? `<a class="source-link" href="${escapeHTML(tests)}" target="_blank" rel="noreferrer">Test file <span>↗</span></a>` : ''}</div></section>` : '';
    const templateParameters = renderTemplateParameters(feature.templateParameters);
    const functionParameters = isFunctionEntity(feature) ? renderFunctionParameters(feature.parameters, feature.returnType, feature.returnTypeRef, true) : '';
    const aggregateContents = renderAggregateContents(feature);
    const isTemplate = feature.templateParameters?.length || ['template-entity', 'function-template', 'class-template', 'variable-template'].includes(feature.entityKind);
    const aliasDefinition = feature.entityKind === 'type-alias' && (feature.aliasedType || feature.aliasedTypeRef)
      ? `<section class="content-section alias-definition"><h2><span class="section-index">A</span> Aliased type</h2><div class="alias-signature"><code>using ${escapeHTML(feature.name)}</code><span>=</span>${referenceMarkup(feature.aliasedType, feature.aliasedTypeRef)}<span>;</span></div></section>` : '';
    return `
      <article class="feature-page">
        <header class="page-header">
          <div class="page-header-copy"><span class="hero-kicker">${escapeHTML(category.name.toUpperCase())} / API REFERENCE</span><h1>${escapeHTML(feature.name)}</h1><p class="page-summary">${escapeHTML(feature.summary || '')}</p><div class="declaration-kind-row"><span class="declaration-kind-badge">${escapeHTML(entityKindLabel(feature.entityKind))}</span>${feature.scopedEnum && feature.entityKind === 'enum' ? '<span class="tag">enum class</span>' : ''}${isTemplate ? '<span class="tag">Templated</span>' : ''}</div>${tags ? `<div class="tag-row">${tags}</div>` : ''}</div>
          <div class="page-actions"><button class="button button-quiet" type="button" data-action="edit-feature" data-feature-id="${escapeHTML(feature.id)}">Edit</button><button class="button button-danger" type="button" data-action="delete-feature" data-feature-id="${escapeHTML(feature.id)}">Delete</button></div>
        </header>
        <div class="metadata-grid">
          ${metadataCard('Namespace', '⌘', feature.namespace)}
          ${metadataCard('Alice version', '◷', feature.introduced)}
          ${metadataCard('Minimum standard', 'C++', feature.standard)}
        </div>
        <section class="content-section" id="overview"><h2><span class="section-index">01</span> Overview</h2><div class="prose-panel">${escapeHTML(feature.description || 'No overview description has been added yet.')}</div></section>
        ${aliasDefinition}
        ${templateParameters}
        ${functionParameters}
        ${aggregateContents}
        ${sections ? `<section class="content-section" id="details"><h2><span class="section-index">05</span> Detailed documentation</h2>${sections}</section>` : ''}
        ${examples ? `<section class="content-section" id="examples"><h2><span class="section-index">06</span> Examples</h2>${examples}</section>` : ''}
        ${sourceSection}
      </article>`;
  }

  function highlightCpp(code) {
    const tokenPattern = /(\/\/[^\n]*|\/\*[\s\S]*?\*\/|"(?:\\.|[^"\\])*"|'(?:\\.|[^'\\])*'|\[\[[^\]]+\]\]|#\s*[A-Za-z_]\w*|\b(?:alignas|alignof|asm|auto|bool|break|case|catch|char|char8_t|char16_t|char32_t|class|concept|const|consteval|constexpr|constinit|const_cast|continue|co_await|co_return|co_yield|decltype|default|delete|do|double|dynamic_cast|else|enum|explicit|export|extern|for|friend|goto|if|inline|int|long|mutable|namespace|new|noexcept|nullptr|operator|private|protected|public|register|reinterpret_cast|requires|return|short|signed|sizeof|static|static_assert|static_cast|struct|switch|template|this|thread_local|throw|try|typedef|typeid|typename|union|unsigned|using|virtual|void|volatile|wchar_t|while|import|module|final|override)\b|\b(?:size_t|ptrdiff_t|int8_t|int16_t|int32_t|int64_t|uint8_t|uint16_t|uint32_t|uint64_t|intmax_t|uintmax_t)\b|\b(?:true|false|nullptr)\b|\b\d+(?:'\d+)*(?:\.\d+)?(?:[eE][+-]?\d+)?(?:[uUlLfFzZ]+)?)/g;
    const keywords = new Set(('alignas alignof asm auto bool break case catch char char8_t char16_t char32_t class concept const consteval constexpr constinit const_cast continue co_await co_return co_yield decltype default delete do double dynamic_cast else enum explicit export extern for friend goto if inline int long mutable namespace new noexcept operator private protected public register reinterpret_cast requires return short signed sizeof static static_assert static_cast struct switch template this thread_local throw try typedef typeid typename union unsigned using virtual void volatile wchar_t while import module final override').split(' '));
    const types = new Set(('size_t ptrdiff_t int8_t int16_t int32_t int64_t uint8_t uint16_t uint32_t uint64_t intmax_t uintmax_t').split(' '));
    let output = '';
    let lastIndex = 0;
    for (const match of code.matchAll(tokenPattern)) {
      const token = match[0];
      const index = match.index;
      output += escapeHTML(code.slice(lastIndex, index));
      let className = '';
      if (token.startsWith('//') || token.startsWith('/*')) className = 'hl-comment';
      else if (token.startsWith('"') || token.startsWith("'")) className = 'hl-string';
      else if (token.startsWith('[[')) className = 'hl-attribute';
      else if (token.startsWith('#')) className = 'hl-preprocessor';
      else if (/^(true|false|nullptr)$/.test(token)) className = 'hl-literal';
      else if (/^\d/.test(token)) className = 'hl-number';
      else if (keywords.has(token)) className = 'hl-keyword';
      else if (types.has(token)) className = 'hl-type';
      output += className ? `<span class="${className}">${escapeHTML(token)}</span>` : escapeHTML(token);
      lastIndex = index + token.length;
    }
    output += escapeHTML(code.slice(lastIndex));
    return output;
  }

  function openCategoryDialog() {
    categoryForm.reset();
    categoryDialog.showModal();
    $('#categoryName').focus();
  }

  function refreshCategorySelect(selectedId = '') {
    const select = $('#featureCategory');
    select.innerHTML = data.categories.map(category => `<option value="${escapeHTML(category.id)}">${escapeHTML(category.name)}</option>`).join('');
    if (selectedId && data.categories.some(category => category.id === selectedId)) select.value = selectedId;
  }

  function addSectionEditor(section = {}) {
    const wrapper = document.createElement('div');
    wrapper.className = 'repeat-item';
    wrapper.dataset.repeatItem = 'section';
    wrapper.innerHTML = `
      <div class="repeat-item-top"><span class="repeat-item-label">DESCRIPTION SECTION</span><button class="remove-repeat" type="button">Remove</button></div>
      <label class="field-label">Section title</label><input class="form-control repeat-title" maxlength="100" value="${escapeHTML(section.title || '')}" placeholder="e.g. Behaviour and guarantees">
      <label class="field-label">Description</label><textarea class="form-control repeat-body" rows="3" placeholder="Explain this part of the API.">${escapeHTML(section.body || '')}</textarea>`;
    sectionsEditor.append(wrapper);
  }

  function addExampleEditor(example = {}) {
    const wrapper = document.createElement('div');
    wrapper.className = 'repeat-item';
    wrapper.dataset.repeatItem = 'example';
    wrapper.innerHTML = `
      <div class="repeat-item-top"><span class="repeat-item-label">C++ USAGE EXAMPLE</span><button class="remove-repeat" type="button">Remove</button></div>
      <label class="field-label">Example title</label><input class="form-control repeat-title" maxlength="100" value="${escapeHTML(example.title || '')}" placeholder="e.g. Basic usage">
      <label class="field-label">Description</label><textarea class="form-control repeat-description" rows="2" placeholder="What does this example demonstrate?">${escapeHTML(example.description || '')}</textarea>
      <label class="field-label">C++ code</label><textarea class="form-control code-input repeat-code" spellcheck="false" autocapitalize="off" autocomplete="off" rows="7" placeholder="#include &lt;...&gt;">${escapeHTML(example.code || '')}</textarea>`;
    examplesEditor.append(wrapper);
  }

  function allEntityOptions(selected = '') {
    return `<option value="">— No linked declaration —</option>${allFeatures().map(({ category, feature }) => `
      <option value="${escapeHTML(feature.id)}"${feature.id === selected ? ' selected' : ''}>${escapeHTML(feature.name)} · ${escapeHTML(category.name)}</option>`).join('')}`;
  }

  function addParameterEditor(parameter = {}, container = parametersEditor, repeatType = 'parameter') {
    const wrapper = document.createElement('div');
    wrapper.className = 'repeat-item parameter-editor-item';
    wrapper.dataset.repeatItem = repeatType;
    wrapper.innerHTML = `
      <div class="repeat-item-top"><span class="repeat-item-label">FUNCTION PARAMETER</span><button class="remove-repeat" type="button">Remove</button></div>
      <div class="form-grid two-columns">
        <div class="field-group"><label class="field-label">Parameter name</label><input class="form-control parameter-name" maxlength="100" value="${escapeHTML(parameter.name || '')}" placeholder="e.g. value"></div>
        <div class="field-group"><label class="field-label">Type</label><input class="form-control parameter-type" value="${escapeHTML(parameter.type || '')}" placeholder="e.g. const Foo&amp;"></div>
      </div>
      <label class="field-label">Link type to API entry</label><select class="form-control parameter-type-ref">${typeEntityOptions(parameter.typeRef || '')}</select>
      <div class="form-grid two-columns"><div class="field-group"><label class="field-label">Default argument</label><input class="form-control parameter-default" value="${escapeHTML(parameter.defaultValue || '')}" placeholder="Optional"></div><div class="field-group"><label class="field-label">Description</label><input class="form-control parameter-description" value="${escapeHTML(parameter.description || '')}" placeholder="Purpose of this parameter"></div></div>`;
    container.append(wrapper);
  }

  function addTemplateParameterEditor(parameter = {}, container = templateParametersEditor, repeatType = 'template-parameter') {
    const wrapper = document.createElement('div');
    wrapper.className = 'repeat-item parameter-editor-item';
    wrapper.dataset.repeatItem = repeatType;
    wrapper.innerHTML = `
      <div class="repeat-item-top"><span class="repeat-item-label">TEMPLATE PARAMETER</span><button class="remove-repeat" type="button">Remove</button></div>
      <div class="form-grid three-columns">
        <div class="field-group"><label class="field-label">Kind</label><select class="form-control template-kind"><option value="type"${(parameter.kind || 'type') === 'type' ? ' selected' : ''}>Type parameter</option><option value="non-type"${parameter.kind === 'non-type' ? ' selected' : ''}>Non-type parameter</option><option value="template"${parameter.kind === 'template' ? ' selected' : ''}>Template template parameter</option></select></div>
        <div class="field-group"><label class="field-label">Name</label><input class="form-control template-name" value="${escapeHTML(parameter.name || '')}" placeholder="e.g. T"></div>
        <div class="field-group"><label class="field-label">Type / constraint</label><input class="form-control template-type" value="${escapeHTML(parameter.type || '')}" placeholder="e.g. std::size_t or typename"></div>
      </div>
      <label class="field-label">Link type / constraint to API entry</label><select class="form-control template-type-ref">${typeEntityOptions(parameter.typeRef || '')}</select>
      <div class="form-grid two-columns"><div class="field-group"><label class="field-label">Default</label><input class="form-control template-default" value="${escapeHTML(parameter.defaultValue || '')}" placeholder="Optional"></div><div class="field-group"><label class="field-label">Description</label><input class="form-control template-description" value="${escapeHTML(parameter.description || '')}" placeholder="Role of this template parameter"></div></div>`;
    container.append(wrapper);
  }

  function addMemberEditor(member = {}) {
    const wrapper = document.createElement('div');
    wrapper.className = 'repeat-item member-editor-item';
    wrapper.dataset.repeatItem = 'member';
    const memberKinds = [
      ['data-member', 'Non-static data member'], ['static-data-member', 'Static data member'],
      ['member-function', 'Member function'], ['static-member-function', 'Static member function'],
      ['member-function-template', 'Member function template'], ['static-member-function-template', 'Static member function template'],
      ['friend-function', 'Friend function'], ['type-alias', 'Type alias'], ['nested-type', 'Nested type'],
      ['nested-class', 'Nested class'], ['nested-struct', 'Nested struct'], ['nested-union', 'Nested union'],
      ['nested-enum', 'Nested enum'], ['enumerator', 'Enumerator'], ['other', 'Other declaration']
    ];
    const kindOptions = memberKinds.map(([key, label]) => `<option value="${key}"${(member.kind || 'data-member') === key ? ' selected' : ''}>${label}</option>`).join('');
    wrapper.innerHTML = `
      <div class="repeat-item-top"><span class="repeat-item-label">CLASS / STRUCT / UNION / ENUM CONTENT</span><button class="remove-repeat" type="button">Remove</button></div>
      <div class="form-grid three-columns">
        <div class="field-group"><label class="field-label">Declaration kind</label><select class="form-control member-kind">${kindOptions}</select></div>
        <div class="field-group"><label class="field-label">Name</label><input class="form-control member-name" value="${escapeHTML(member.name || '')}" placeholder="e.g. m_value"></div>
        <div class="field-group"><label class="field-label">Access</label><select class="form-control member-access"><option value="public"${(member.access || 'public') === 'public' ? ' selected' : ''}>public</option><option value="protected"${member.access === 'protected' ? ' selected' : ''}>protected</option><option value="private"${member.access === 'private' ? ' selected' : ''}>private</option></select></div>
      </div>
      <div class="form-grid two-columns">
        <div class="field-group"><label class="field-label">Type / return type</label><input class="form-control member-type" value="${escapeHTML(member.type || member.returnType || '')}" placeholder="e.g. std::uint32_t"></div>
        <div class="field-group"><label class="field-label">Link type to API entry</label><select class="form-control member-type-ref">${typeEntityOptions(member.typeRef || member.returnTypeRef || '')}</select></div>
      </div>
      <div class="form-grid two-columns">
        <div class="field-group"><label class="field-label">Initializer / enumerator value</label><input class="form-control member-value" value="${escapeHTML(member.value || '')}" placeholder="e.g. 0"></div>
        <div class="field-group"><label class="field-label">Link member name to declaration</label><select class="form-control member-entity-ref">${allEntityOptions(member.entityRef || '')}</select></div>
      </div>
      <label class="inline-checkbox member-static-field"><input class="member-static" type="checkbox"${member.isStatic ? ' checked' : ''}><span><strong>Static declaration</strong><small>Useful for static data members and static member functions.</small></span></label>
      <label class="field-label">Description</label><textarea class="form-control textarea-small member-description" rows="2" placeholder="Document this declaration.">${escapeHTML(member.description || '')}</textarea>
      <div class="member-function-options">
        <div class="member-template-parameters-list"></div>
        <div class="member-parameter-actions"><span class="member-subheading">TEMPLATE PARAMETERS</span><button class="add-repeat-button add-member-template-parameter" type="button">+ Add template parameter</button></div>
        <div class="member-parameters-list">${(member.parameters || []).map(() => '').join('')}</div>
        <div class="member-parameter-actions"><span class="member-subheading">FUNCTION PARAMETERS</span><button class="add-repeat-button add-member-parameter" type="button">+ Add parameter</button></div>
      </div>`;
    const parameterList = $('.member-parameters-list', wrapper);
    (member.parameters || []).forEach(parameter => addParameterEditor(parameter, parameterList, 'member-parameter'));
    const memberTemplateList = $('.member-template-parameters-list', wrapper);
    (member.templateParameters || []).forEach(parameter => addTemplateParameterEditor(parameter, memberTemplateList, 'member-template-parameter'));
    wrapper.querySelector('.member-parameters-list').addEventListener('click', event => {
      const removeButton = event.target.closest('.remove-repeat');
      if (removeButton) removeButton.closest('.repeat-item')?.remove();
    });
    const memberKindSelect = $('.member-kind', wrapper);
    const syncMemberEditor = () => {
      const functionKinds = ['member-function', 'static-member-function', 'friend-function', 'member-function-template', 'static-member-function-template'];
      $('.member-function-options', wrapper).hidden = !functionKinds.includes(memberKindSelect.value);
      $('.member-static-field', wrapper).hidden = !['static-data-member', 'static-member-function', 'static-member-function-template'].includes(memberKindSelect.value) && !member.isStatic;
    };
    memberKindSelect.addEventListener('change', syncMemberEditor);
    syncMemberEditor();
    membersEditor.append(wrapper);
  }

  function updateKindSpecificEditor() {
    const kind = $('#featureKind').value;
    const isEnum = kind === 'enum';
    const isTemplate = ['template-entity', 'function-template', 'class-template', 'variable-template'].includes(kind) || templateParametersEditor.children.length > 0;
    const isFunction = ['free-function', 'function-template', 'function-like-macro'].includes(kind) || parametersEditor.children.length > 0 || Boolean($('#featureReturnType').value) || Boolean($('#featureReturnTypeRef').value);
    const isAggregate = ['class', 'struct', 'union', 'enum', 'class-template', 'template-entity'].includes(kind) || membersEditor.children.length > 0;
    $('#scopedEnumField').hidden = !isEnum;
    $('#aliasEditorSection').hidden = kind !== 'type-alias';
    $('#templateEditorSection').hidden = !isTemplate;
    $('#functionEditorSection').hidden = !isFunction;
    $('#membersEditorSection').hidden = !isAggregate;
  }

  function openFeatureEditor(feature = null, preferredCategoryId = activeCategoryId) {
    if (!data.categories.length) {
      showToast('Create a category before adding a feature.', true);
      openCategoryDialog();
      return;
    }
    featureForm.reset();
    $('#featureId').value = feature?.id || '';
    $('#featureDialogTitle').textContent = feature ? 'Edit feature' : 'Add feature';
    $('#saveFeatureButton').textContent = feature ? 'Save changes' : 'Save feature';
    refreshCategorySelect(feature ? findFeature(feature.id)?.category.id : preferredCategoryId);
    $('#featureName').value = feature?.name || '';
    $('#featureSummary').value = feature?.summary || '';
    $('#featureDescription').value = feature?.description || '';
    $('#namespaceValue').value = feature?.namespace?.value || '';
    $('#namespaceDescription').value = feature?.namespace?.description || '';
    $('#introducedValue').value = feature?.introduced?.value || data.project.version;
    $('#introducedDescription').value = feature?.introduced?.description || '';
    $('#standardValue').value = feature?.standard?.value || '';
    $('#standardDescription').value = feature?.standard?.description || '';
    $('#sourceUrl').value = feature?.sourceUrl || '';
    $('#testUrl').value = feature?.testUrl || '';
    $('#featureTags').value = (feature?.tags || []).join(', ');
    $('#featureKind').innerHTML = entityKindOptions(feature?.entityKind || 'other');
    $('#scopedEnum').checked = Boolean(feature?.scopedEnum);
    $('#aliasedType').value = feature?.aliasedType || '';
    $('#aliasedTypeRef').innerHTML = typeEntityOptions(feature?.aliasedTypeRef || '');
    $('#featureReturnType').value = feature?.returnType || '';
    $('#featureReturnTypeRef').innerHTML = typeEntityOptions(feature?.returnTypeRef || '');
    sectionsEditor.innerHTML = '';
    examplesEditor.innerHTML = '';
    templateParametersEditor.innerHTML = '';
    parametersEditor.innerHTML = '';
    membersEditor.innerHTML = '';
    (feature?.sections || []).forEach(addSectionEditor);
    (feature?.examples || []).forEach(addExampleEditor);
    (feature?.templateParameters || []).forEach(addTemplateParameterEditor);
    (feature?.parameters || []).forEach(parameter => addParameterEditor(parameter));
    (feature?.members || []).forEach(addMemberEditor);
    updateKindSpecificEditor();
    featureDialog.showModal();
    $('#featureName').focus();
  }

  function closeSidebar() {
    sidebar.classList.remove('open');
    sidebarScrim.classList.remove('visible');
  }

  function toggleSidebar() {
    sidebar.classList.toggle('open');
    sidebarScrim.classList.toggle('visible');
  }

  function exportDocument() {
    const content = JSON.stringify(data, null, 2);
    const blob = new Blob([content], { type: 'application/json' });
    const url = URL.createObjectURL(blob);
    const link = document.createElement('a');
    link.href = url;
    link.download = `${slugify(data.project.name || 'alice')}-api-reference.json`;
    document.body.append(link);
    link.click();
    link.remove();
    URL.revokeObjectURL(url);
    showToast('Documentation exported as JSON.');
  }

  async function importDocument(file) {
    if (!file) return;
    try {
      const parsed = JSON.parse(await file.text());
      if (!isValidDocument(parsed)) throw new Error('The file does not contain a valid documentation structure.');
      data = normalizeDocument(parsed);
      activeCategoryId = data.categories[0]?.id ?? null;
      activeFeatureId = data.categories[0]?.features[0]?.id ?? null;
      expandedCategories = new Set(data.categories.map(category => category.id));
      persist();
      render();
      showToast('Documentation imported successfully.');
    } catch (error) {
      showToast(error.message || 'Could not import this JSON file.', true);
    } finally {
      importFile.value = '';
    }
  }

  function collectParameterRows(container, repeatType = 'parameter') {
    return $$(`.repeat-item[data-repeat-item="${repeatType}"]`, container).map(item => ({
      id: String(item.dataset.id || makeId('parameter')),
      name: $('.parameter-name', item).value.trim(),
      type: $('.parameter-type', item).value.trim(),
      typeRef: $('.parameter-type-ref', item).value,
      defaultValue: $('.parameter-default', item).value.trim(),
      description: $('.parameter-description', item).value.trim()
    })).filter(parameter => parameter.name || parameter.type || parameter.typeRef || parameter.description || parameter.defaultValue);
  }

  function collectTemplateParameters(container = templateParametersEditor, repeatType = 'template-parameter') {
    return $$('.repeat-item[data-repeat-item="' + repeatType + '"]', container).map(item => ({
      id: makeId('template-parameter'),
      kind: $('.template-kind', item).value,
      name: $('.template-name', item).value.trim(),
      type: $('.template-type', item).value.trim(),
      typeRef: $('.template-type-ref', item).value,
      defaultValue: $('.template-default', item).value.trim(),
      description: $('.template-description', item).value.trim()
    })).filter(parameter => parameter.name || parameter.type || parameter.defaultValue || parameter.description);
  }

  function collectMembers() {
    return $$('.repeat-item[data-repeat-item="member"]', membersEditor).map(item => {
      const kind = $('.member-kind', item).value;
      const type = $('.member-type', item).value.trim();
      const typeRef = $('.member-type-ref', item).value;
      const parameters = collectParameterRows($('.member-parameters-list', item), 'member-parameter');
      const templateParameters = collectTemplateParameters($('.member-template-parameters-list', item), 'member-template-parameter');
      return {
        id: String(item.dataset.id || makeId('member')),
        kind,
        name: $('.member-name', item).value.trim(),
        type: ['member-function', 'static-member-function', 'friend-function', 'member-function-template', 'static-member-function-template'].includes(kind) ? '' : type,
        typeRef: ['member-function', 'static-member-function', 'friend-function', 'member-function-template', 'static-member-function-template'].includes(kind) ? '' : typeRef,
        entityRef: $('.member-entity-ref', item).value,
        value: $('.member-value', item).value.trim(),
        access: $('.member-access', item).value,
        isStatic: $('.member-static', item).checked || ['static-data-member', 'static-member-function', 'static-member-function-template'].includes(kind),
        returnType: ['member-function', 'static-member-function', 'friend-function', 'member-function-template', 'static-member-function-template'].includes(kind) ? type : '',
        returnTypeRef: ['member-function', 'static-member-function', 'friend-function', 'member-function-template', 'static-member-function-template'].includes(kind) ? typeRef : '',
        description: $('.member-description', item).value.trim(),
        parameters,
        templateParameters
      };
    }).filter(member => member.name || member.type || member.typeRef || member.returnType || member.returnTypeRef || member.value || member.description || member.entityRef || member.parameters.length || member.templateParameters.length);
  }

  function collectFeatureForm() {
    const form = new FormData(featureForm);
    const sections = $$('.repeat-item[data-repeat-item="section"]', sectionsEditor).map(item => ({
      title: $('.repeat-title', item).value.trim(),
      body: $('.repeat-body', item).value.trim()
    })).filter(section => section.title || section.body);
    const examples = $$('.repeat-item[data-repeat-item="example"]', examplesEditor).map(item => ({
      title: $('.repeat-title', item).value.trim(),
      description: $('.repeat-description', item).value.trim(),
      code: $('.repeat-code', item).value
    })).filter(example => example.title || example.description || example.code);
    return {
      id: String(form.get('id') || makeId('feature')),
      name: String(form.get('name') || '').trim(),
      summary: String(form.get('summary') || '').trim(),
      description: String(form.get('description') || '').trim(),
      entityKind: String(form.get('entityKind') || 'other'),
      scopedEnum: Boolean(form.get('scopedEnum')),
      aliasedType: String(form.get('aliasedType') || '').trim(),
      aliasedTypeRef: String(form.get('aliasedTypeRef') || ''),
      namespace: { value: String(form.get('namespaceValue') || '').trim(), description: String(form.get('namespaceDescription') || '').trim() },
      introduced: { value: String(form.get('introducedValue') || '').trim(), description: String(form.get('introducedDescription') || '').trim() },
      standard: { value: String(form.get('standardValue') || '').trim(), description: String(form.get('standardDescription') || '').trim() },
      returnType: String(form.get('returnType') || '').trim(),
      returnTypeRef: String(form.get('returnTypeRef') || ''),
      templateParameters: collectTemplateParameters(),
      parameters: collectParameterRows(parametersEditor),
      members: collectMembers(),
      sourceUrl: String(form.get('sourceUrl') || '').trim(),
      testUrl: String(form.get('testUrl') || '').trim(),
      tags: String(form.get('tags') || '').split(',').map(tag => tag.trim()).filter(Boolean),
      sections,
      examples
    };
  }

  function saveCategory(event) {
    event.preventDefault();
    const name = $('#categoryName').value.trim();
    if (!name) return;
    if (data.categories.some(category => category.name.toLowerCase() === name.toLowerCase())) {
      showToast('A category with that name already exists.', true);
      return;
    }
    const category = {
      id: makeId(slugify(name)),
      name,
      description: $('#categoryDescription').value.trim(),
      features: []
    };
    data.categories.push(category);
    activeCategoryId = category.id;
    activeFeatureId = null;
    expandedCategories.add(category.id);
    persist();
    categoryDialog.close();
    render();
    showToast(`Category “${name}” created.`);
  }

  function saveFeature(event) {
    event.preventDefault();
    const feature = collectFeatureForm();
    const targetCategoryId = $('#featureCategory').value;
    const targetCategory = data.categories.find(category => category.id === targetCategoryId);
    if (!targetCategory) {
      showToast('Choose a valid category for this feature.', true);
      return;
    }
    if (!feature.name || !feature.summary) {
      showToast('Feature name and short summary are required.', true);
      return;
    }
    const existing = feature.id ? findFeature(feature.id) : null;
    if (existing) {
      existing.category.features = existing.category.features.filter(item => item.id !== feature.id);
    }
    targetCategory.features.push(feature);
    activeCategoryId = targetCategory.id;
    activeFeatureId = feature.id;
    expandedCategories.add(targetCategory.id);
    persist();
    featureDialog.close();
    render();
    showToast(existing ? 'Feature updated.' : 'Feature added.');
  }

  async function copyExample(index) {
    const selected = currentFeature();
    const code = selected?.feature.examples?.[index]?.code;
    if (code === undefined) return;
    try {
      await navigator.clipboard.writeText(code);
      showToast('Code copied to clipboard.');
    } catch {
      const temporary = document.createElement('textarea');
      temporary.value = code;
      temporary.style.position = 'fixed';
      temporary.style.opacity = '0';
      document.body.append(temporary);
      temporary.select();
      const copied = document.execCommand('copy');
      temporary.remove();
      showToast(copied ? 'Code copied to clipboard.' : 'Clipboard access was unavailable.', !copied);
    }
  }

  function handleAction(actionElement) {
    const action = actionElement.dataset.action;
    const categoryId = actionElement.dataset.categoryId;
    const featureId = actionElement.dataset.featureId;
    if (action === 'open-category') {
      setCurrentCategory(categoryId);
    } else if (action === 'open-feature') {
      openFeature(categoryId, featureId);
    } else if (action === 'open-reference') {
      const target = findFeature(featureId);
      if (target) openFeature(target.category.id, target.feature.id);
      else showToast('The referenced API entry no longer exists.', true);
    } else if (action === 'toggle-category') {
      expandedCategories.has(categoryId) ? expandedCategories.delete(categoryId) : expandedCategories.add(categoryId);
      renderSidebar();
    } else if (action === 'add-feature' || action === 'add-feature-in-category') {
      openFeatureEditor(null, categoryId || activeCategoryId);
    } else if (action === 'add-category') {
      openCategoryDialog();
    } else if (action === 'edit-feature') {
      const found = findFeature(featureId);
      if (found) openFeatureEditor(found.feature, found.category.id);
    } else if (action === 'delete-feature') {
      const found = findFeature(featureId);
      if (found && window.confirm(`Delete “${found.feature.name}” from the documentation? This cannot be undone unless you have an exported backup.`)) {
        found.category.features = found.category.features.filter(feature => feature.id !== featureId);
        activeCategoryId = found.category.id;
        activeFeatureId = null;
        persist();
        render();
        showToast('Feature deleted.');
      }
    } else if (action === 'copy-example') {
      copyExample(Number(actionElement.dataset.exampleIndex));
    }
  }

  // Navigation and page actions use delegation so dynamically rendered entries stay interactive.
  categoryNav.addEventListener('click', event => {
    const actionElement = event.target.closest('[data-action]');
    if (actionElement) handleAction(actionElement);
  });
  view.addEventListener('click', event => {
    const actionElement = event.target.closest('[data-action]');
    if (actionElement) handleAction(actionElement);
  });

  $('#addCategoryButton').addEventListener('click', openCategoryDialog);
  $('#addFeatureButton').addEventListener('click', () => openFeatureEditor());
  $('#exportButton').addEventListener('click', exportDocument);
  $('#importButton').addEventListener('click', () => importFile.click());
  importFile.addEventListener('change', () => importDocument(importFile.files?.[0]));
  $('#openSidebar').addEventListener('click', toggleSidebar);
  $('#closeSidebar').addEventListener('click', closeSidebar);
  sidebarScrim.addEventListener('click', closeSidebar);
  $('#homeLink').addEventListener('click', event => {
    event.preventDefault();
    activeCategoryId = null;
    activeFeatureId = null;
    render();
    closeSidebar();
  });
  docSearch.addEventListener('input', renderSidebar);
  categoryForm.addEventListener('submit', saveCategory);
  featureForm.addEventListener('submit', saveFeature);
  $('#addSectionButton').addEventListener('click', () => addSectionEditor());
  $('#addExampleButton').addEventListener('click', () => addExampleEditor());
  $('#addTemplateParameterButton').addEventListener('click', () => addTemplateParameterEditor());
  $('#addParameterButton').addEventListener('click', () => addParameterEditor());
  $('#addMemberButton').addEventListener('click', () => addMemberEditor());
  $('#featureKind').addEventListener('change', updateKindSpecificEditor);

  [sectionsEditor, examplesEditor, templateParametersEditor, parametersEditor, membersEditor].forEach(editor => editor.addEventListener('click', event => {
    const removeButton = event.target.closest('.remove-repeat');
    if (removeButton) removeButton.closest('.repeat-item')?.remove();
    const addMemberTemplateParameter = event.target.closest('.add-member-template-parameter');
    if (addMemberTemplateParameter) {
      const member = addMemberTemplateParameter.closest('[data-repeat-item="member"]');
      addTemplateParameterEditor({}, $('.member-template-parameters-list', member), 'member-template-parameter');
    }
    const addMemberParameter = event.target.closest('.add-member-parameter');
    if (addMemberParameter) {
      const member = addMemberParameter.closest('[data-repeat-item="member"]');
      const list = $('.member-parameters-list', member);
      addParameterEditor({}, list, 'member-parameter');
    }
  }));

  $$('[data-close-dialog]').forEach(button => button.addEventListener('click', () => {
    const dialog = document.getElementById(button.dataset.closeDialog);
    if (dialog?.open) dialog.close();
  }));

  [categoryDialog, featureDialog].forEach(dialog => dialog.addEventListener('click', event => {
    if (event.target === dialog) dialog.close();
  }));

  document.addEventListener('keydown', event => {
    const target = event.target;
    const isTyping = target instanceof HTMLElement && (target.isContentEditable || ['INPUT', 'TEXTAREA', 'SELECT'].includes(target.tagName));
    if (event.key === '/' && !isTyping && !categoryDialog.open && !featureDialog.open) {
      event.preventDefault();
      docSearch.focus();
    }
    if (event.key === 'Escape') closeSidebar();
  });

  render();
})();
